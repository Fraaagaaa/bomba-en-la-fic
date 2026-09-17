import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'models.dart';
import 'repositories.dart';
import 'l10n/app_localizations.dart';
import 'expense_form_view.dart';

class ExpenseDetailsView extends StatefulWidget {
  final Expense expense;

  const ExpenseDetailsView({super.key, required this.expense});

  @override
  State<ExpenseDetailsView> createState() => _ExpenseDetailsViewState();
}

class _ExpenseDetailsViewState extends State<ExpenseDetailsView> {
  Expense? _fullExpense;
  bool _isLoading = true;

  @override
  void initState() {
    super.initState();
    _loadFullExpense();
  }

  Future<void> _loadFullExpense() async {
    if (!mounted) return;
    setState(() => _isLoading = true);
    
    try {
      final repo = Provider.of<ExpenseRepository>(context, listen: false);
      _fullExpense = await repo.getExpenseById(widget.expense.isarId);
    } catch (e) {
      // Fallback
    } finally {
      if (mounted) setState(() => _isLoading = false);
    }
  }

  @override
  Widget build(BuildContext context) {
    final l10n = AppLocalizations.of(context)!;
    
    final expense = _fullExpense ?? widget.expense;
    final payer = expense.payer.value;
    final participants = expense.participantsList;
    
    // Cuánto "consume" o "gasta" cada uno teóricamente
    final debitPerParticipant = participants.isNotEmpty 
        ? (expense.amount / participants.length) 
        : 0.0;

    return Scaffold(
      appBar: AppBar(
        title: Text(expense.description),
        actions: [
          IconButton(
            icon: const Icon(Icons.edit),
            onPressed: () async {
              final didChange = await Navigator.push(
                context,
                MaterialPageRoute(
                  builder: (context) => ExpenseFormView(isEditing: true, expense: expense),
                ),
              );
              if (didChange == true) {
                await _loadFullExpense();
              }
            },
          )
        ],
      ),
      body: _isLoading
          ? const Center(child: CircularProgressIndicator())
          : ListView(
              padding: const EdgeInsets.all(16.0),
              children: [
                Card(
                  elevation: 2,
                  child: Padding(
                    padding: const EdgeInsets.all(16.0),
                    child: Column(
                      crossAxisAlignment: CrossAxisAlignment.start,
                      children: [
                        Text(
                          '${expense.amount.toStringAsFixed(2)}${l10n.currencySymbol}',
                          style: const TextStyle(fontSize: 32, fontWeight: FontWeight.bold),
                        ),
                        const SizedBox(height: 8),
                        Text(
                          '${l10n.labelPaidBy}: ${payer?.name ?? "..."}',
                          style: const TextStyle(fontSize: 18, fontStyle: FontStyle.italic, color: Colors.grey),
                        ),
                        Text(
                          '${l10n.labelDate}: ${expense.date.day}/${expense.date.month}/${expense.date.year}',
                          style: const TextStyle(fontSize: 16),
                        ),
                      ],
                    ),
                  ),
                ),
                const SizedBox(height: 24),

                Text(
                  '${l10n.labelParticipants} (${participants.length})',
                  style: Theme.of(context).textTheme.titleMedium,
                ),
                const SizedBox(height: 8),
                if (participants.isEmpty)
                  const Padding(
                    padding: EdgeInsets.all(8.0),
                    child: Text('No hay participantes.'),
                  )
                else
                  ...participants.map((friend) {
                    // LÓGICA CORREGIDA DE VISUALIZACIÓN
                    final isPayer = friend.isarId == payer?.isarId;
                    final paidAmount = isPayer ? expense.amount : 0.0;
                    final netBalanceInExpense = paidAmount - debitPerParticipant;

                    String text;
                    Color color;

                    // Usamos una pequeña tolerancia (epsilon) para evitar problemas de coma flotante
                    if (netBalanceInExpense > 0.001) {
                      // Si el saldo es positivo, significa que pagó más de lo que le toca -> Le deben
                      text = 'Le deben ${netBalanceInExpense.toStringAsFixed(2)}${l10n.currencySymbol}';
                      color = Colors.green;
                    } else if (netBalanceInExpense < -0.001) {
                      // Si es negativo, debe dinero
                      text = 'Debe ${netBalanceInExpense.abs().toStringAsFixed(2)}${l10n.currencySymbol}';
                      color = Colors.red;
                    } else {
                      // Si es 0 (ej: pagó exactamente su parte o nadie debe nada)
                      text = 'Al día';
                      color = Colors.grey;
                    }

                    return ListTile(
                      leading: const Icon(Icons.person),
                      title: Text(friend.name),
                      trailing: Text(
                        text,
                        style: TextStyle(color: color, fontSize: 16, fontWeight: FontWeight.bold),
                      ),
                    );
                  }),
              ],
            ),
    );
  }
}