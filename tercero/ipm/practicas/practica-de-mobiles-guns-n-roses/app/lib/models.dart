import 'package:isar/isar.dart';

part 'models.g.dart';

@collection
class Friend {
  Id isarId = Isar.autoIncrement;

  final int id; 
  final String name;
  
  double totalCreditBalance; 
  double totalDebitBalance;  

  Friend({
    this.id = 0,
    required this.name, 
    this.totalCreditBalance = 0.0, 
    this.totalDebitBalance = 0.0,
  });

  double get netBalance => totalCreditBalance - totalDebitBalance;

  factory Friend.fromJson(Map<String, dynamic> json) {
    return Friend(
      id: json['id'] ?? 0,
      name: json['name'] ?? '',
      totalCreditBalance: (json['credit_balance'] ?? 0).toDouble(),
      totalDebitBalance: (json['debit_balance'] ?? 0).toDouble(),
    );
  }

  Map<String, dynamic> toJson() {
    return {
      'name': name,
    };
  }
}

@collection
class Expense {
  Id isarId = Isar.autoIncrement;

  final int id;
  String description; 
  DateTime date;      
  double amount;      
  
  final payer = IsarLink<Friend>();
  final participants = IsarLinks<Friend>(); 

  int? payerId;
  List<int> participantIds = [];

  Expense({
    this.id = 0,
    required this.description,
    required this.date,
    required this.amount,
    this.payerId,
    this.participantIds = const [],
  });

  // Helper definition to fix build error.
  // In a real app we might need to fetch full objects, but for now we create partial objects from IDs
  // or return an empty list if that satisfies the UI (though UI likely needs names).
  // Given the error `expense.participantsList`, let's return a generated list.
  List<Friend> get participantsList {
    return participantIds.map((id) => Friend(id: id, name: 'Friend $id')).toList();
  }

  factory Expense.fromJson(Map<String, dynamic> json) {
    var expense = Expense(
      id: json['id'] ?? 0,
      description: json['description'] ?? '',
      date: DateTime.tryParse(json['date'] ?? '') ?? DateTime.now(),
      amount: (json['amount'] ?? 0).toDouble(),
      payerId: json['payer_id'],
    );
    return expense;
  }
}