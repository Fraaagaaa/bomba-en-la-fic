import 'package:flutter/material.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:provider/provider.dart';
import 'package:isar/isar.dart';
import 'dart:math';
import 'package:splitwithfriends/main.dart';
import 'package:splitwithfriends/models.dart';
import 'package:splitwithfriends/repositories.dart';
import 'package:splitwithfriends/l10n/app_localizations.dart';
import 'package:flutter_localizations/flutter_localizations.dart';
import 'package:splitwithfriends/friends_view.dart';
import 'package:splitwithfriends/expenses_view.dart';
import 'package:splitwithfriends/settle_debt_dialog.dart';

// ==========================================================================
// 1. MOCKS SIMPLIFICADOS (Memoria Pura)
// ==========================================================================

class MockIsar implements Isar {
  @override
  Future<T> writeTxn<T>(Future<T> Function() callback, {bool silent = false}) async => callback();
  @override
  dynamic noSuchMethod(Invocation invocation) => super.noSuchMethod(invocation);
}

class MockFriendRepository implements FriendRepository {
  final List<Friend> friendsDB = [];
  bool shouldThrowError = false; 

  MockFriendRepository(Isar isar);

  @override
  Future<List<Friend>> getAllFriends() async {
    if (shouldThrowError) throw Exception("Error simulado");
    return List.from(friendsDB);
  }

  @override
  Future<void> saveFriend(Friend friend) async {
    if (shouldThrowError) throw Exception("Error simulado");
    if (friend.isarId == Isar.autoIncrement) {
      // Asignar ID manual para evitar problemas
      friend.isarId = friendsDB.isEmpty ? 1 : friendsDB.map((e) => e.isarId).reduce(max) + 1;
      friendsDB.add(friend);
    } else {
      final index = friendsDB.indexWhere((f) => f.isarId == friend.isarId);
      if (index != -1) friendsDB[index] = friend;
    }
  }

  @override
  Future<void> deleteFriend(Id friendId) async {
    friendsDB.removeWhere((f) => f.isarId == friendId);
  }

  @override
  Future<Friend?> getFriendById(Id id) async {
    try {
      return friendsDB.firstWhere((f) => f.isarId == id);
    } catch (e) {
      return null;
    }
  }
  
  @override
  Future<void> settleDebt(Friend payer, Friend receiver, double amount) async {
    final p = friendsDB.firstWhere((f) => f.isarId == payer.isarId);
    final r = friendsDB.firstWhere((f) => f.isarId == receiver.isarId);
    p.totalDebitBalance = max(0, p.totalDebitBalance - amount);
    r.totalCreditBalance = max(0, r.totalCreditBalance - amount);
  }
  
  @override
  Future<void> settleDebts(Friend friend) async {
    final f = friendsDB.firstWhere((fr) => fr.isarId == friend.isarId);
    f.totalCreditBalance = 0;
    f.totalDebitBalance = 0;
  }
  @override
  Isar get isar => MockIsar();
}

// Estructura simple para guardar datos sin depender de IsarLinks
class _MockExpenseData {
  int id;
  String description;
  double amount;
  DateTime date;
  int? payerId;
  Set<int> participantIds;

  _MockExpenseData({
    required this.id,
    required this.description,
    required this.amount,
    required this.date,
    this.payerId,
    required this.participantIds,
  });
}

class MockExpenseRepository implements ExpenseRepository {
  final Map<int, _MockExpenseData> _storage = {};
  final MockFriendRepository friendRepo;

  MockExpenseRepository(Isar isar, this.friendRepo);

  // Convierte los datos guardados en un objeto Expense real
  Expense _createExpenseFromData(_MockExpenseData data) {
    final e = Expense(
      description: data.description,
      amount: data.amount,
      date: data.date,
    );
    e.isarId = data.id;

    if (data.payerId != null) {
      try {
        e.payer.value = friendRepo.friendsDB.firstWhere((f) => f.isarId == data.payerId);
      } catch (_) {}
    }

    if (data.participantIds.isNotEmpty) {
      final parts = friendRepo.friendsDB.where((f) => data.participantIds.contains(f.isarId)).toList();
      // HOOK: Populate debugMockParticipants for tests!
      debugMockParticipants[e] = parts;
    }
    return e;
  }

  void _recalculateBalances() {
    for (var f in friendRepo.friendsDB) {
      f.totalCreditBalance = 0;
      f.totalDebitBalance = 0;
    }
    for (var data in _storage.values) {
      if (data.payerId != null && data.participantIds.isNotEmpty) {
        try {
          final payer = friendRepo.friendsDB.firstWhere((f) => f.isarId == data.payerId);
          payer.totalCreditBalance += data.amount;
        } catch (_) {}

        final split = data.amount / data.participantIds.length;
        for (var pid in data.participantIds) {
          try {
            final part = friendRepo.friendsDB.firstWhere((f) => f.isarId == pid);
            part.totalDebitBalance += split;
          } catch (_) {}
        }
      }
    }
  }

  @override
  Future<List<Expense>> getAllExpenses() async {
    return _storage.values.map(_createExpenseFromData).toList();
  }

  @override
  Future<void> saveExpense(Expense expense) async {
    int id = expense.isarId;
    if (id == Isar.autoIncrement) {
      id = _storage.isEmpty ? 1 : (_storage.keys.isEmpty ? 1 : _storage.keys.reduce(max) + 1);
      expense.isarId = id;
    }

    // Use participantsList (the hook) to read what was passed, because expense.participants might be empty if it's new
    // But wait, if we create a new expense in test, we add into expense.participants...
    // But IsarLinks failed to add?
    // In test, use: debugMockParticipants[expense] = [friends]?
    // Let's modify tests to use debugMockParticipants too if IsarLinks fails.

    Set<int> pIds = {};
    if (debugMockParticipants.containsKey(expense)) {
        pIds = debugMockParticipants[expense]!.map((f) => f.isarId).toSet();
    } else {
        // Fallback (though likely empty in test env)
        try {
          pIds = expense.participants.toList().map((f) => f.isarId).toSet();
        } catch (_) {}
    }

    final data = _MockExpenseData(
      id: id,
      description: expense.description,
      amount: expense.amount,
      date: expense.date,
      payerId: expense.payer.value?.isarId,
      participantIds: pIds,
    );

    _storage[id] = data;
    _recalculateBalances();
  }

  @override
  Future<void> deleteExpense(Id isarId) async {
    _storage.remove(isarId);
    _recalculateBalances();
  }

  @override
  Future<Expense?> getExpenseById(Id id) async {
    final data = _storage[id];
    if (data == null) return null;
    return _createExpenseFromData(data);
  }
  
  @override
  Future<List<Expense>> getExpensesPaidByFriend(Friend friend) async {
    return _storage.values
        .where((d) => d.payerId == friend.isarId)
        .map(_createExpenseFromData)
        .toList();
  }
  
  @override
  Future<List<Expense>> getExpensesOwedByFriend(Friend friend) async {
    return _storage.values
        .where((d) => d.participantIds.contains(friend.isarId))
        .map(_createExpenseFromData)
        .toList();
  }
  @override
  Isar get isar => MockIsar();
}

// ==========================================================================
// 2. HELPER DE UI PARA TESTS (Evita conflictos de GlobalKeys)
// ==========================================================================

class TestMainScreen extends StatefulWidget {
  const TestMainScreen({super.key});
  @override
  State<TestMainScreen> createState() => _TestMainScreenState();
}

class _TestMainScreenState extends State<TestMainScreen> {
  // Claves locales para cada test
  final friendsKey = GlobalKey<FriendsViewState>();
  final expensesKey = GlobalKey<ExpensesViewState>();

  void _showSettleDebtDialog(BuildContext context) async {
    final bool? didSettle = await showDialog(
      context: context,
      builder: (_) => const SettleDebtDialog(),
    );
    if (didSettle == true) {
      friendsKey.currentState?.loadFriends();
      expensesKey.currentState?.loadExpenses();
    }
  }

  @override
  Widget build(BuildContext context) {
    final l10n = AppLocalizations.of(context);
    return DefaultTabController(
      length: 2,
      child: Scaffold(
        appBar: AppBar(
          title: Text(l10n?.appTitle ?? 'Test'),
          bottom: TabBar(tabs: [
            Tab(text: l10n?.friendsTab ?? 'Friends'),
            Tab(text: l10n?.expensesTab ?? 'Expenses'),
          ]),
        ),
        body: TabBarView(children: [
          FriendsView(key: friendsKey),
          ExpensesView(key: expensesKey),
        ]),
        persistentFooterButtons: [
          TextButton(
            onPressed: () => _showSettleDebtDialog(context),
            child: Text(l10n?.btnSettle ?? 'LIQUIDAR DEUDA'),
          ),
        ],
      ),
    );
  }
}

Widget createTestApp({
  required FriendRepository friendRepo,
  required ExpenseRepository expenseRepo,
  required Isar isar,
}) {
  return MultiProvider(
    providers: [
      Provider<Isar>.value(value: isar),
      Provider<FriendRepository>.value(value: friendRepo),
      Provider<ExpenseRepository>.value(value: expenseRepo),
    ],
    child: const MaterialApp(
      localizationsDelegates: [
        AppLocalizations.delegate,
        GlobalMaterialLocalizations.delegate,
        GlobalWidgetsLocalizations.delegate,
        GlobalCupertinoLocalizations.delegate,
      ],
      supportedLocales: [Locale('en'), Locale('es')],
      locale: Locale('es'), // IDIOMA FORZADO A ESPAÑOL
      home: TestMainScreen(),
    ),
  );
}

void main() {
  late MockIsar mockIsar;
  late MockFriendRepository mockFriendRepo;
  late MockExpenseRepository mockExpenseRepo;

  setUp(() {
    mockIsar = MockIsar();
    mockFriendRepo = MockFriendRepository(mockIsar);
    mockExpenseRepo = MockExpenseRepository(mockIsar, mockFriendRepo);
    debugMockParticipants.clear(); // Limpiar hooks entre tests
  });

  group('Pruebas de Casos de Uso (Diseño UI)', () {
    
    testWidgets('UC-06: Ver lista de amigos', (WidgetTester tester) async {
      await mockFriendRepo.saveFriend(Friend(name: 'Ana'));
      await mockFriendRepo.saveFriend(Friend(name: 'Beto'));

      await tester.pumpWidget(createTestApp(friendRepo: mockFriendRepo, expenseRepo: mockExpenseRepo, isar: mockIsar));
      await tester.pumpAndSettle();

      expect(find.textContaining('Ana'), findsOneWidget);
      expect(find.textContaining('Beto'), findsOneWidget);
    });

    testWidgets('UC-08: Ver balance general', (WidgetTester tester) async {
      await mockFriendRepo.saveFriend(Friend(name: 'Carlos'));
      await tester.pumpWidget(createTestApp(friendRepo: mockFriendRepo, expenseRepo: mockExpenseRepo, isar: mockIsar));
      await tester.pumpAndSettle();
      expect(find.text('Carlos - 0.00€'), findsOneWidget);
    });

    testWidgets('UC-07: Ver detalle de un amigo', (WidgetTester tester) async {
      final amigo = Friend(name: 'Elena');
      await mockFriendRepo.saveFriend(amigo);

      final friends = await mockFriendRepo.getAllFriends();
      final elena = friends.firstWhere((f) => f.name == 'Elena');
      
      final gasto = Expense(description: 'Regalo', date: DateTime.now(), amount: 30);
      gasto.payer.value = Friend(name: 'Otro');
      // gasto.participants.add(elena);
      debugMockParticipants[gasto] = [elena];
      
      await mockExpenseRepo.saveExpense(gasto);

      await tester.pumpWidget(createTestApp(friendRepo: mockFriendRepo, expenseRepo: mockExpenseRepo, isar: mockIsar));
      await tester.pumpAndSettle();

      await tester.tap(find.text('VER DETALLES'));
      await tester.pumpAndSettle();
      await tester.pump(const Duration(seconds: 1)); // Espera para cargar detalles

      expect(find.text('Balance General de Elena'), findsOneWidget);
      expect(find.text('Regalo'), findsOneWidget);
    });

    testWidgets('UC-02: Crear gasto', (WidgetTester tester) async {
      await mockFriendRepo.saveFriend(Friend(name: 'Ana'));
      await mockFriendRepo.saveFriend(Friend(name: 'Beto'));

      await tester.pumpWidget(createTestApp(friendRepo: mockFriendRepo, expenseRepo: mockExpenseRepo, isar: mockIsar));
      await tester.pumpAndSettle();

      await tester.tap(find.text('GASTOS'));
      await tester.pumpAndSettle();
      await tester.tap(find.byType(FloatingActionButton));
      await tester.pumpAndSettle();

      await tester.enterText(find.widgetWithText(TextFormField, 'Descripción'), 'Cena');
      await tester.enterText(find.widgetWithText(TextFormField, 'Monto'), '100');
      
      await tester.tap(find.byType(DropdownButtonFormField<Friend>));
      await tester.pumpAndSettle();
      await tester.tap(find.text('Ana').last);
      await tester.pumpAndSettle();

      await tester.tap(find.text('Beto'));
      await tester.pumpAndSettle();

      await tester.tap(find.text('CONFIRMAR'));
      await tester.pumpAndSettle();

      expect(find.text('Cena - 100.00€'), findsOneWidget);
    });

    testWidgets('UC-01: Ver lista de gastos', (WidgetTester tester) async {
      final amigo = Friend(name: 'Juan');
      await mockFriendRepo.saveFriend(amigo);
      final juan = (await mockFriendRepo.getAllFriends()).first;
      
      final gasto = Expense(description: 'Taxi', date: DateTime.now(), amount: 15);
      gasto.payer.value = juan;
      // gasto.participants.add(juan);
      debugMockParticipants[gasto] = [juan];
      await mockExpenseRepo.saveExpense(gasto);

      await tester.pumpWidget(createTestApp(friendRepo: mockFriendRepo, expenseRepo: mockExpenseRepo, isar: mockIsar));
      await tester.pumpAndSettle();

      await tester.tap(find.text('GASTOS'));
      await tester.pumpAndSettle();

      expect(find.text('Taxi - 15.00€'), findsOneWidget);
    });

    testWidgets('UC-05: Ver detalle de un gasto', (WidgetTester tester) async {
      await mockFriendRepo.saveFriend(Friend(name: 'Carlos'));
      await mockFriendRepo.saveFriend(Friend(name: 'Diana'));
      final friends = await mockFriendRepo.getAllFriends();
      final carlos = friends.firstWhere((f) => f.name == 'Carlos');
      final diana = friends.firstWhere((f) => f.name == 'Diana');

      final gasto = Expense(description: 'Viaje', date: DateTime.now(), amount: 200);
      gasto.payer.value = carlos;
      // gasto.participants.addAll([carlos, diana]);
      debugMockParticipants[gasto] = [carlos, diana];
      await mockExpenseRepo.saveExpense(gasto);

      await tester.pumpWidget(createTestApp(friendRepo: mockFriendRepo, expenseRepo: mockExpenseRepo, isar: mockIsar));
      await tester.pumpAndSettle();

      await tester.tap(find.text('GASTOS'));
      await tester.pumpAndSettle();
      
      await tester.tap(find.text('VER DETALLES'));
      await tester.pumpAndSettle();
      await tester.pump(const Duration(seconds: 1)); // Espera para cargar detalles

      expect(find.text('Viaje'), findsOneWidget);
      expect(find.textContaining('Carlos'), findsWidgets);
      expect(find.textContaining('Diana'), findsWidgets); 
      expect(find.textContaining('200.00'), findsWidgets);
    });

    testWidgets('UC-03: Editar gasto', (WidgetTester tester) async {
      await mockFriendRepo.saveFriend(Friend(name: 'Ana'));
      final ana = (await mockFriendRepo.getAllFriends()).first;
      
      final gasto = Expense(description: 'Comida', date: DateTime.now(), amount: 50);
      gasto.payer.value = ana;
      // gasto.participants.add(ana);
      debugMockParticipants[gasto] = [ana];
      await mockExpenseRepo.saveExpense(gasto);

      await tester.pumpWidget(createTestApp(friendRepo: mockFriendRepo, expenseRepo: mockExpenseRepo, isar: mockIsar));
      await tester.pumpAndSettle();

      await tester.tap(find.text('GASTOS'));
      await tester.pumpAndSettle();

      await tester.tap(find.text('VER DETALLES'));
      await tester.pumpAndSettle();

      final editButton = find.byIcon(Icons.edit);
      await tester.tap(editButton);
      await tester.pumpAndSettle();

      await tester.enterText(find.widgetWithText(TextFormField, 'Monto'), '80');
      await tester.tap(find.text('CONFIRMAR'));
      
      await tester.pumpAndSettle(); 
      await tester.pump(const Duration(seconds: 1)); 

      expect(find.textContaining('80.00'), findsOneWidget);
    });

    testWidgets('UC-04: Eliminar gasto', (WidgetTester tester) async {
      final gasto = Expense(description: 'GastoBorrar', date: DateTime.now(), amount: 10);
      await mockExpenseRepo.saveExpense(gasto);

      await tester.pumpWidget(createTestApp(friendRepo: mockFriendRepo, expenseRepo: mockExpenseRepo, isar: mockIsar));
      await tester.pumpAndSettle();

      await tester.tap(find.text('GASTOS'));
      await tester.pumpAndSettle();

      expect(find.text('GastoBorrar - 10.00€'), findsOneWidget);

      await tester.drag(find.byType(Dismissible), const Offset(-500.0, 0.0));
      await tester.pumpAndSettle();

      expect(find.text('GastoBorrar - 10.00€'), findsNothing);
      expect(find.text('Gasto eliminado (UC-04)'), findsOneWidget);
    });

    testWidgets('Caso Extra: Liquidar Deuda', (WidgetTester tester) async {
      await mockFriendRepo.saveFriend(Friend(name: 'Deudor'));
      await mockFriendRepo.saveFriend(Friend(name: 'Acreedor'));
      
      // Simular deudas iniciales
      final friends = await mockFriendRepo.getAllFriends();
      friends[0].totalDebitBalance = 50;
      friends[1].totalCreditBalance = 50;

      await tester.pumpWidget(createTestApp(friendRepo: mockFriendRepo, expenseRepo: mockExpenseRepo, isar: mockIsar));
      await tester.pumpAndSettle();

      await tester.tap(find.text('LIQUIDAR DEUDA'));
      await tester.pumpAndSettle();

      await tester.tap(find.byType(DropdownButtonFormField<Friend>).at(0));
      await tester.pumpAndSettle();
      await tester.tap(find.text('Deudor').last);
      await tester.pumpAndSettle();

      await tester.tap(find.byType(DropdownButtonFormField<Friend>).at(1));
      await tester.pumpAndSettle();
      await tester.tap(find.text('Acreedor').last);
      await tester.pumpAndSettle();

      await tester.enterText(find.widgetWithText(TextFormField, 'Monto'), '50');
      
      final btnFinder = find.text('Liquidar');
      if (btnFinder.evaluate().isNotEmpty) {
         await tester.tap(btnFinder);
      } else {
         await tester.tap(find.text('Settle'));
      }
      await tester.pumpAndSettle();

      expect(find.textContaining('50.00'), findsOneWidget);
    });
  });

  group('Pruebas de Errores', () {
     testWidgets('Error: Crear gasto vacío', (WidgetTester tester) async {
      await mockFriendRepo.saveFriend(Friend(name: 'Test'));
      await tester.pumpWidget(createTestApp(friendRepo: mockFriendRepo, expenseRepo: mockExpenseRepo, isar: mockIsar));
      
      await tester.tap(find.text('GASTOS'));
      await tester.pumpAndSettle();
      await tester.tap(find.byType(FloatingActionButton));
      await tester.pumpAndSettle();

      await tester.tap(find.text('CONFIRMAR'));
      await tester.pumpAndSettle();

      expect(find.text('CREAR GASTO'), findsOneWidget);
      expect(find.text('Requerido'), findsWidgets);
    });
    
    testWidgets('Error: Liquidar deuda incompleta', (WidgetTester tester) async {
      await tester.pumpWidget(createTestApp(friendRepo: mockFriendRepo, expenseRepo: mockExpenseRepo, isar: mockIsar));
      await tester.pumpAndSettle();

      await tester.tap(find.text('LIQUIDAR DEUDA'));
      await tester.pumpAndSettle();

      final btnFinder = find.text('Liquidar');
      if (btnFinder.evaluate().isNotEmpty) {
         await tester.tap(btnFinder);
      } else {
         await tester.tap(find.text('Settle'));
      }
      await tester.pumpAndSettle();

      expect(find.text('Liquidar Deuda'), findsOneWidget);
      expect(find.byType(Form), findsOneWidget); 
    });
    
    testWidgets('Manejo de error al cargar amigos', (WidgetTester tester) async {
      mockFriendRepo.shouldThrowError = true;
      await tester.pumpWidget(createTestApp(friendRepo: mockFriendRepo, expenseRepo: mockExpenseRepo, isar: mockIsar));
      await tester.pumpAndSettle();
      expect(find.text('No se pudo recuperar la lista de amigos'), findsOneWidget);
    });

    testWidgets('Manejo de error al guardar amigo', (WidgetTester tester) async {
      await tester.pumpWidget(createTestApp(friendRepo: mockFriendRepo, expenseRepo: mockExpenseRepo, isar: mockIsar));
      await tester.pumpAndSettle();
      mockFriendRepo.shouldThrowError = true;
      await tester.tap(find.byType(FloatingActionButton));
      await tester.pumpAndSettle();
      await tester.enterText(find.byType(TextField), 'Nuevo');
      await tester.tap(find.text('Añadir'));
      await tester.pumpAndSettle();
      expect(find.text('No se pudo añadir al amigo Nuevo'), findsOneWidget);
    });
  });
}