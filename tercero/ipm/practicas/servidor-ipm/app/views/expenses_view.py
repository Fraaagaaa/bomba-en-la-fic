
import gi
gi.require_version("Gtk", "4.0")

from gi.repository import Gtk, Gdk
from app.presenters.expenses_presenter import ExpensesPresenter


class ExpensesView(Gtk.Box):

    def __init__(self, api_client):
        super().__init__(
            orientation=Gtk.Orientation.VERTICAL,
            spacing=15,
            margin_top=20, margin_bottom=20, margin_start=20, margin_end=20
        )

        self.presenter = ExpensesPresenter(self, api_client)
        self._expenses_data = []
        self.selected_expense = None

        # --- Título ---
        titulo = Gtk.Label(label="Split - Gastos")
        titulo.add_css_class("section-title")
        self.append(titulo)

        # --- Lista de gastos ---
        self.expenses_box = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=5)
        # Opcional: mismo padding que en la lista de amigos
        self.expenses_box.add_css_class("friends-list")

        scrolled = Gtk.ScrolledWindow()
        scrolled.set_policy(Gtk.PolicyType.NEVER, Gtk.PolicyType.AUTOMATIC)
        scrolled.set_child(self.expenses_box)
        scrolled.set_vexpand(True)
        self.append(scrolled)

        # --- Botones principales ---
        buttons_box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=10)
        buttons_box.set_halign(Gtk.Align.CENTER)

        self.añadir_gasto = Gtk.Button(label="Create expense")
        self.añadir_gasto.add_css_class("action-button")
        self.añadir_gasto.connect("clicked", self.on_create_expense_clicked)

        self.mostrar_lista_gastos = Gtk.Button(label="Show expense list")
        self.mostrar_lista_gastos.add_css_class("action-button")
        self.mostrar_lista_gastos.connect("clicked", self.on_show_list_clicked)

        buttons_box.append(self.añadir_gasto)
        buttons_box.append(self.mostrar_lista_gastos)
        self.append(buttons_box)

        # Cargar datos iniciales
        self.load_expenses()

    def load_expenses(self):
        """Carga la lista de gastos"""
        # Datos de ejemplo
        self._expenses_data = [
            {"id": 1, "description": "Expense 1", "date": "2025/10/01", "amount": 50.0, "friends": "Friend 1, Friend 2", "credits": 25.0},
            {"id": 2, "description": "Expense 2", "date": "2025/10/02", "amount": 75.0, "friends": "Friend 2, Friend 3", "credits": 37.5},
            {"id": 3, "description": "Expense 3", "date": "2025/10/03", "amount": 100.0, "friends": "Friend 1, Friend 4", "credits": 50.0},
            {"id": 4, "description": "Expense 4", "date": "2025/10/04", "amount": 25.0, "friends": "Friend 3, Friend 4", "credits": 12.5},
        ]
        self.update_expenses_list()

    def update_expenses_list(self):
        """Actualiza la visualización de la lista de gastos con estilo tipo Amigos"""
        # Limpiar lista actual
        child = self.expenses_box.get_first_child()
        while child:
            next_child = child.get_next_sibling()
            self.expenses_box.remove(child)
            child = next_child

        # Añadir gastos
        for expense in self._expenses_data:
            row = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=10)
            # Reutiliza el mismo look que en Amigos (línea gris + padding)
            row.add_css_class("friend-row")
            # Márgenes para que no queden pegados a los bordes
            row.set_margin_top(5)
            row.set_margin_bottom(5)
            row.set_margin_start(10)
            row.set_margin_end(10)

            desclabel = Gtk.Label(label=expense["description"])
            desclabel.set_hexpand(True)
            desclabel.set_halign(Gtk.Align.START)

            amountlabel = Gtk.Label(label=f'${expense["amount"]:.2f}')
            amountlabel.set_halign(Gtk.Align.END)

            row.append(desclabel)
            row.append(amountlabel)

            gesture = Gtk.GestureClick.new()
            gesture.connect("pressed", self.on_expense_selected, expense)
            row.add_controller(gesture)

            self.expenses_box.append(row)

    def on_create_expense_clicked(self, button):
        """Abre diálogo para crear gasto"""
        dialog = Gtk.Dialog(title="Split - Gastos - Crear")
        dialog.set_transient_for(self.get_root())
        dialog.set_modal(True)
        dialog.set_default_size(400, 300)

        content = dialog.get_content_area()
        content.set_spacing(10)
        content.set_margin_top(10)
        content.set_margin_bottom(10)
        content.set_margin_start(10)
        content.set_margin_end(10)

        # Grid para campos
        grid = Gtk.Grid()
        grid.set_row_spacing(10)
        grid.set_column_spacing(10)

        # Description
        grid.attach(Gtk.Label(label="Description"), 0, 0, 1, 1)
        desc_entry = Gtk.Entry()
        grid.attach(desc_entry, 1, 0, 1, 1)

        # Date (YYYY/MM/DD)
        grid.attach(Gtk.Label(label="Date (YYYY/MM/DD)"), 0, 1, 1, 1)
        date_entry = Gtk.Entry()
        date_entry.set_placeholder_text("2025/10/10")
        grid.attach(date_entry, 1, 1, 1, 1)

        # Amount
        grid.attach(Gtk.Label(label="Amount"), 0, 2, 1, 1)
        amount_entry = Gtk.Entry()
        grid.attach(amount_entry, 1, 2, 1, 1)

        # Balance
        grid.attach(Gtk.Label(label="Balance"), 0, 3, 1, 1)
        balance_entry = Gtk.Entry()
        grid.attach(balance_entry, 1, 3, 1, 1)

        content.append(grid)

        # Botones
        button_box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=10)
        button_box.set_halign(Gtk.Align.CENTER)

        ok_btn = Gtk.Button(label="OK")
        cancel_btn = Gtk.Button(label="Cancel")

        ok_btn.connect("clicked", self.on_create_expense_ok, dialog, desc_entry, date_entry, amount_entry, balance_entry)
        cancel_btn.connect("clicked", lambda b: dialog.close())

        button_box.append(cancel_btn)
        button_box.append(ok_btn)
        content.append(button_box)

        dialog.show()

    def on_create_expense_ok(self, button, dialog, desc_entry, date_entry, amount_entry, balance_entry):
        """Confirma creación de gasto"""
        description = desc_entry.get_text().strip()
        date = date_entry.get_text().strip()

        try:
            amount = float(amount_entry.get_text())
            balance = float(balance_entry.get_text()) if balance_entry.get_text() else 0.0
        except ValueError:
            return

        if description and date:
            new_id = max([e["id"] for e in self._expenses_data]) + 1 if self._expenses_data else 1
            self._expenses_data.append({
                "id": new_id,
                "description": description,
                "date": date,
                "amount": amount,
                "friends": "Various",
                "credits": balance
            })
            self.update_expenses_list()
        dialog.close()

    def on_expense_selected(self, gesture, n_press, x, y, expense):
        """Selecciona gasto para editar"""
        self.selected_expense = expense
        self.show_edit_dialog()

    def show_edit_dialog(self):
        """Muestra diálogo de edición de gasto"""
        dialog = Gtk.Dialog(title="Split - Gastos - Editar")
        dialog.set_transient_for(self.get_root())
        dialog.set_modal(True)
        dialog.set_default_size(400, 350)

        content = dialog.get_content_area()
        content.set_spacing(10)
        content.set_margin_top(10)
        content.set_margin_bottom(10)
        content.set_margin_start(10)
        content.set_margin_end(10)

        # Grid para campos
        grid = Gtk.Grid()
        grid.set_row_spacing(10)
        grid.set_column_spacing(10)

        # Description
        grid.attach(Gtk.Label(label="Change description"), 0, 0, 1, 1)
        desc_entry = Gtk.Entry()
        desc_entry.set_text(self.selected_expense["description"])
        grid.attach(desc_entry, 1, 0, 1, 1)

        # Date
        grid.attach(Gtk.Label(label="Change date"), 0, 1, 1, 1)
        date_entry = Gtk.Entry()
        date_entry.set_text(self.selected_expense["date"])
        grid.attach(date_entry, 1, 1, 1, 1)

        # Amount
        grid.attach(Gtk.Label(label="Change amount"), 0, 2, 1, 1)
        amount_entry = Gtk.Entry()
        amount_entry.set_text(str(self.selected_expense["amount"]))
        grid.attach(amount_entry, 1, 2, 1, 1)

        content.append(grid)

        # Botones
        button_box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=10)
        button_box.set_halign(Gtk.Align.CENTER)

        remove_btn = Gtk.Button(label="Remove expense")
        ok_btn = Gtk.Button(label="OK")

        remove_btn.connect("clicked", self.on_remove_expense, dialog)
        ok_btn.connect("clicked", self.on_edit_expense_ok, dialog, desc_entry, date_entry, amount_entry)

        button_box.append(remove_btn)
        button_box.append(ok_btn)
        content.append(button_box)

        dialog.show()

    def on_edit_expense_ok(self, button, dialog, desc_entry, date_entry, amount_entry):
        """Confirma edición de gasto"""
        if self.selected_expense:
            self.selected_expense["description"] = desc_entry.get_text().strip()
            self.selected_expense["date"] = date_entry.get_text().strip()
            try:
                self.selected_expense["amount"] = float(amount_entry.get_text())
            except ValueError:
                pass
            self.update_expenses_list()
        dialog.close()

    def on_remove_expense(self, button, dialog):
        """Elimina gasto"""
        if self.selected_expense:
            self._expenses_data = [e for e in self._expenses_data if e["id"] != self.selected_expense["id"]]
            self.update_expenses_list()
        dialog.close()


    def on_show_list_clicked(self, button):
        """Muestra lista detallada de gastos en tabla"""
        dialog = Gtk.Dialog(title="Split - Gastos - Lista")
        dialog.set_transient_for(self.get_root())
        dialog.set_modal(True)
        dialog.set_default_size(700, 500)
    
        content = dialog.get_content_area()
        content.set_spacing(10)
    
        # Crear tabla con headers
        grid = Gtk.Grid()
        grid.set_row_spacing(5)
        grid.set_column_spacing(10)
        grid.add_css_class("expense-table")
    
        # Headers
        headers = ["ID", "Description", "Date", "Amount", "Friends", "Credits"]
        for i, header in enumerate(headers):
            label = Gtk.Label(label=header)
            label.add_css_class("table-header")
            grid.attach(label, i, 0, 1, 1)
    
        # Datos
        for row_idx, expense in enumerate(self._expenses_data, 1):
            values = [
                str(expense["id"]),
                expense["description"],
                expense["date"],
                f"${expense['amount']:.2f}",
                expense["friends"],
                f"${expense['credits']:.2f}"
            ]
            for col, value in enumerate(values):
                label = Gtk.Label(label=value)
                label.add_css_class("table-cell")
                grid.attach(label, col, row_idx, 1, 1)
    
        # Wrapper con margen superior para separar la tabla del borde
        wrapper = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=0)
        wrapper.set_margin_top(16)       # margen arriba
        wrapper.append(grid)
    
        scrolled = Gtk.ScrolledWindow()
        scrolled.set_child(wrapper)
        scrolled.set_vexpand(True)
        content.append(scrolled)
    
        # Botón cerrar
        close_btn = Gtk.Button(label="Close")
        close_btn.connect("clicked", lambda b: dialog.close())
        # close_btn.set_halign(Gtk.Align.END)
        close_btn.set_margin_start(10)
        close_btn.set_margin_end(10)
        close_btn.set_margin_bottom(10)
        content.append(close_btn)
    
        dialog.show()
