import 'dart:async';
import 'dart:io';
import 'dart:convert';
import 'package:http/http.dart' as http;
import 'models.dart';

final String serverURL = Platform.isAndroid ? "10.0.2.2" : "127.0.0.1";
final String serverPort = "8000";

class ServerException implements Exception {
  final String msg;
  ServerException(this.msg);
  @override
  String toString() => msg;
}

class SplitWithMeAPIService {
  
  // --- FRIENDS ---

  Future<List<Friend>> fetchFriends() async {
    var uri = Uri.http("$serverURL:$serverPort", "friends");
    try {
      var response = await http.get(uri);
      if (response.statusCode == 200) {
        var data = json.decode(response.body) as List;
        return data.map((item) => Friend.fromJson(item)).toList();
      } else {
        throw ServerException("Error fetching friends: ${response.statusCode}");
      }
    } catch (e) {
      throw ServerException("Service unavailable: $e");
    }
  }

  Future<Friend> addFriend(String name) async {
    var uri = Uri.http("$serverURL:$serverPort", "friends/");
    try {
      var response = await http.post(
        uri,
        headers: {"Content-Type": "application/json"},
        body: json.encode({'name': name}),
      );
      if (response.statusCode == 201) {
        return Friend.fromJson(json.decode(response.body));
      } else {
        throw ServerException("Error creating friend");
      }
    } catch (e) {
      throw ServerException("Service unavailable: $e");
    }
  }

  Future<void> deleteFriend(int id) async {
    var uri = Uri.http("$serverURL:$serverPort", "friends/$id");
    try {
      var response = await http.delete(uri);
      if (response.statusCode != 204) {
        throw ServerException("Failed to delete friend");
      }
    } catch (e) {
      throw ServerException("Service unavailable: $e");
    }
  }

  Future<Friend> getFriend(int id) async {
    var uri = Uri.http("$serverURL:$serverPort", "friends/$id");
    try {
      var response = await http.get(uri);
      if (response.statusCode == 200) {
        return Friend.fromJson(json.decode(response.body));
      } else {
        throw ServerException("Error fetching friend");
      }
    } catch (e) {
      throw ServerException("Service unavailable: $e");
    }
  }

  // --- EXPENSES ---

  Future<List<Expense>> fetchExpenses() async {
    var uri = Uri.http("$serverURL:$serverPort", "expenses");
    try {
      var response = await http.get(uri);
      if (response.statusCode == 200) {
        var data = json.decode(response.body) as List;
        List<Expense> expenses = [];
        for (var item in data) {
          var expense = Expense.fromJson(item);
          expenses.add(expense);
        }
        return expenses;
      } else {
        throw ServerException("Error fetching expenses");
      }
    } catch (e) {
      throw ServerException("Service unavailable: $e");
    }
  }

  Future<void> createExpense(String desc, String date, double amount, int payerId, List<int> participantIds) async {
    var uri = Uri.http("$serverURL:$serverPort", "expenses/");
    var body = json.encode({
      'description': desc,
      'date': date,
      'amount': amount,
      'payer_id': payerId,
      'participant_ids': participantIds
    });

    try {
      var response = await http.post(
        uri,
        headers: {"Content-Type": "application/json"},
        body: body,
      );
      if (response.statusCode != 201) {
        var msg = "Error creating expense";
        try {
          var errorData = json.decode(response.body);
          if (errorData['detail'] != null) msg = errorData['detail'];
        } catch (_) {}
        throw ServerException(msg);
      }
    } catch (e) {
      throw ServerException(e.toString());
    }
  }

  Future<void> deleteExpense(int id) async {
    var uri = Uri.http("$serverURL:$serverPort", "expenses/$id");
    try {
      var response = await http.delete(uri);
      if (response.statusCode != 204) {
        throw ServerException("Failed to delete expense");
      }
    } catch (e) {
      throw ServerException("Service unavailable: $e");
    }
  }


  Future<Expense> getExpense(int id) async {
    var uri = Uri.http("$serverURL:$serverPort", "expenses/$id");
    try {
      var response = await http.get(uri);
      if (response.statusCode == 200) {
        return Expense.fromJson(json.decode(response.body));
      } else {
        throw ServerException("Error fetching expense");
      }
    } catch (e) {
      throw ServerException("Service unavailable: $e");
    }
  }
}