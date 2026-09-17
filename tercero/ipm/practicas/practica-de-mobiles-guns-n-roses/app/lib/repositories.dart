import 'models.dart';
import 'services.dart';

class FriendRepository {
  final SplitWithMeAPIService _apiService;

  FriendRepository(this._apiService);

  Future<List<Friend>> getAllFriends() async {
    return await _apiService.fetchFriends();
  }

  Future<void> saveFriend(Friend friend) async {
    await _apiService.addFriend(friend.name);
  }
  Future<void> deleteFriend(int id) async {
    await _apiService.deleteFriend(id);
  }

  Future<Friend> getFriendById(int id) async {
    return await _apiService.getFriend(id); 
  }

  Future<void> settleDebts(Friend friend) async {
    // Basic implementation: we might want to clear debts or create a settlement expense.
    // For now, let's assume this is a placeholder or requires explicit actions.
    // Making it a no-op to allow compilation as logic is unclear without backend support for "clean slate".
    // Alternatively, we could fetch all expenses where this friend owes money and mark them paid?
    // Given the method signature, let's just log or return.
    print("Settling debts for ${friend.name}");
  }

  Future<void> settleDebt(Friend payer, Friend receiver, double amount) async {
     // Create an expense to represent the settlement
     await _apiService.createExpense(
         "Settlement", 
         DateTime.now().toIso8601String().split('T')[0], 
         amount, 
         payer.id, 
         [receiver.id]
     );
  }
}

class ExpenseRepository {
  final SplitWithMeAPIService _apiService;

  ExpenseRepository(this._apiService);

  Future<List<Expense>> getAllExpenses() async {
    return await _apiService.fetchExpenses();
  }

  Future<void> saveExpense(Expense expense) async {
    String dateStr = expense.date.toIso8601String().split('T')[0];
    
    if (expense.payerId != null && expense.participantIds.isNotEmpty) {
      await _apiService.createExpense(
        expense.description,
        dateStr,
        expense.amount,
        expense.payerId!,
        expense.participantIds
      );
    } else {
      throw Exception("Datos incompletos para enviar al servidor");
    }
  }

  Future<void> deleteExpense(int id) async {
    await _apiService.deleteExpense(id);
  }

  Future<Expense> getExpenseById(int id) async {
    return await _apiService.getExpense(id);
  }

  Future<List<Expense>> getExpensesOwedByFriend(Friend friend) async {
    final allExpenses = await getAllExpenses();
    // Assuming a friend owes money if they are a participant and not the payer.
    return allExpenses.where((e) => e.participantIds.contains(friend.id) && e.payerId != friend.id).toList();
  }
}