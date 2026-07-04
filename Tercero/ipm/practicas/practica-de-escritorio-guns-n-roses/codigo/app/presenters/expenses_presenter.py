from app.services.api_client import ApiClient
import threading
from gi.repository import GLib
try:
    from app.i18n import _
except ImportError:
    _ = lambda x: x

class ExpensesPresenter:
    def __init__(self, view, api_client: ApiClient):
        self.view = view
        self.api_client = api_client
        self._friends = []

    def load_expenses(self, query=None):
        """Inicia la carga asíncrona de gastos."""
        GLib.idle_add(self.view.start_thinking)
        threading.Thread(
            target=self._slow_load_expenses,
            args=(query,),
            daemon=True
        ).start()

    def _slow_load_expenses(self, query=None):
        """Método en hilo secundario para cargar gastos."""
        try:
            expenses = self.api_client.list_expenses(query)
            GLib.idle_add(self.view.show_expenses, expenses)
        except Exception as e:
            GLib.idle_add(self.view.show_error, f"Error cargando gastos: {e}")
        finally:
            GLib.idle_add(self.view.stop_thinking)

    def select_expense(self, expense_id):
        """
        Esta función ya no parece necesaria si la selección de gasto
        solo abre el diálogo de edición con datos ya cargados.
        Si necesitara recargar datos específicos del gasto, se haría asíncrona.
        """
        pass

    def load_friends_for_selection(self):
        """Inicia la carga asíncrona de amigos para los diálogos."""
        threading.Thread(
            target=self._slow_load_friends_for_selection,
            daemon=True
        ).start()

    def _slow_load_friends_for_selection(self):
        """Método en hilo secundario para cargar amigos."""
        try:
            self._friends = self.api_client.list_friends()
            GLib.idle_add(self.view.populate_friend_selectors, self._friends)
        except Exception as e:
            GLib.idle_add(self.view.show_error, f"Error cargando amigos para selección: {e}")
            GLib.idle_add(self.view.populate_friend_selectors, [])

    def add_expense(self, description: str, date_str: str, amount_str: str, payer_id: int, participant_ids: list[int]):
        """Valida datos e inicia la creación asíncrona del gasto."""
        try:
            # Validaciones síncronas primero
            if not all([description, date_str, amount_str, payer_id is not None, participant_ids]):
                raise ValueError(_("All values are required, including payer and participants"))
            if payer_id not in participant_ids:
                raise ValueError(_("Payer must be one of the participants"))

            amount = float(amount_str)
            if amount <= 0:
                raise ValueError(_("Amount must be a positive number"))
            GLib.idle_add(self.view.start_thinking_dialog, self.view.create_dialog)
            threading.Thread(
                target=self._slow_add_expense,
                args=(description, date_str, amount, payer_id, participant_ids),
                daemon=True
            ).start()

        except ValueError as ve:
             self.view.show_error(f"{_('Error in expense data')}: {ve}")
        except Exception as e:
            self.view.show_error(f"{_('Error procesando datos')}: {e}")

    def _slow_add_expense(self, description, date_str, amount, payer_id, participant_ids):
        """Método en hilo secundario para crear el gasto."""
        try:
            created_expense = self.api_client.create_expense(
                description=description,
                date=date_str,
                amount=amount,
                payer_id=payer_id,
                participant_ids=participant_ids
            )
            desc = created_expense.get('description', 'Nuevo')
            message = _("Expense '{name}' added successfully.").format(name=desc)
            GLib.idle_add(self.view.show_status, message)
            GLib.idle_add(self.load_expenses)
            GLib.idle_add(self.view.close_create_dialog)

        except Exception as e:
            # Error: pedir al hilo principal mostrar el error detallado
            detail = self._extract_error_detail(e)
            GLib.idle_add(self.view.show_error, f"Error creando gasto: {detail}")
        finally:
            # Siempre: pedir al hilo principal detener feedback del diálogo
            GLib.idle_add(self.view.stop_thinking_dialog, self.view.create_dialog)

    def update_expense(self, expense_id, data: dict):
        """Valida datos e inicia la actualización asíncrona del gasto."""
        try:
            amount = data.get('amount', 0)
            if float(amount) <= 0:
                raise ValueError(_("Amount must be a positive number"))
            if data.get('payer_id') not in data.get('participant_ids', []):
                raise ValueError(_("Payer must be one of the participants"))
            if not data.get('participant_ids'):
                raise ValueError("Debe haber al menos un participante.")


            GLib.idle_add(self.view.start_thinking_dialog, self.view.edit_dialog)
            threading.Thread(
                target=self._slow_update_expense,
                args=(expense_id, data),
                daemon=True
            ).start()
        except ValueError as ve:
             self.view.show_error(f"{_('Error in expense data')}: {ve}")
        except Exception as e:
            self.view.show_error(f"{_('Error procesando datos')}: {e}")


    def _slow_update_expense(self, expense_id, data: dict):
        """Método en hilo secundario para actualizar el gasto."""
        try:
            self.api_client.update_expense(expense_id, data) # Llamada de red
            GLib.idle_add(self.view.show_status, "Gasto actualizado correctamente.")
            GLib.idle_add(self.load_expenses) # Recarga asíncrona
            GLib.idle_add(self.view.close_edit_dialog)
        except Exception as e:
            detail = self._extract_error_detail(e)
            GLib.idle_add(self.view.show_error, f"Error al actualizar gasto: {detail}")
        finally:
            GLib.idle_add(self.view.stop_thinking_dialog, self.view.edit_dialog)

    def delete_expense(self, expense_id):
        """Inicia la eliminación asíncrona del gasto."""
        GLib.idle_add(self.view.start_thinking_dialog, self.view.edit_dialog)
        threading.Thread(
            target=self._slow_delete_expense,
            args=(expense_id,),
            daemon=True
        ).start()

    def _slow_delete_expense(self, expense_id):
        """Método en hilo secundario para eliminar el gasto."""
        try:
            GLib.idle_add(self.view.show_status, _("Expense deleted successfully"))
            self.api_client.delete_expense(expense_id)
            GLib.idle_add(self.load_expenses) 
            GLib.idle_add(self.view.close_edit_dialog)
        except Exception as e:
            detail = self._extract_error_detail(e)
            GLib.idle_add(self.view.show_error, f"{_('Error deleting expense')}: {detail}")
        finally:
            GLib.idle_add(self.view.stop_thinking_dialog, self.view.edit_dialog)

    def _extract_error_detail(self, e: Exception) -> str:
        """Función auxiliar para obtener un mensaje de error más útil desde la API."""
        detail = str(e)
        if hasattr(e, 'response') and e.response is not None:
            try:
                error_data = e.response.json()
                detail = error_data.get('detail', e.response.text)
            except:
                detail = e.response.text if e.response.text else detail
        return detail
