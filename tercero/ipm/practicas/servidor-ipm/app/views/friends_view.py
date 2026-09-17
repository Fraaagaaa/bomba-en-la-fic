import gi

gi.require_version("Gtk", "4.0")

from gi.repository import Gtk, Gdk

from app.presenters.friends_presenter import FriendsPresenter

class FriendsView(Gtk.Box):

    def __init__(self, api_client):
        super().__init__(orientation=Gtk.Orientation.VERTICAL, spacing=15,
                         margin_top=20, margin_bottom=20, margin_start=20, margin_end=20)
        
        self.presenter = FriendsPresenter(self, api_client)
        self._friends_data = []
        self.selected_friend = None

        # --- Título ---
        title_label = Gtk.Label(label="Split - Amigos")
        title_label.add_css_class("section-title")
        self.append(title_label)

        # --- Lista de amigos ---
        self.friends_box = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=5)
        self.friends_box.add_css_class("friends-list")
        
        scrolled = Gtk.ScrolledWindow()
        scrolled.set_policy(Gtk.PolicyType.NEVER, Gtk.PolicyType.AUTOMATIC)
        scrolled.set_child(self.friends_box)
        scrolled.set_vexpand(True)
        
        self.append(scrolled)

        # --- Botones principales ---
        buttons_box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=10)
        buttons_box.set_halign(Gtk.Align.CENTER)

        #self.add_friend_btn = Gtk.Button(label="Add friend")
        #self.add_friend_btn.add_css_class("action-button")
        #self.add_friend_btn.connect("clicked", self.on_add_friend_clicked)

        self.show_list_btn = Gtk.Button(label="Show friend list")
        self.show_list_btn.add_css_class("action-button")
        self.show_list_btn.connect("clicked", self.on_show_list_clicked)

        #buttons_box.append(self.add_friend_btn)
        buttons_box.append(self.show_list_btn)
        
        self.append(buttons_box)

        # Cargar datos iniciales
        self.load_friends()

    def load_friends(self):
        """Carga la lista de amigos"""
        # Simular datos para coincidir con el PDF
        self._friends_data = [
            {"id": 1, "name": "Friend 1", "credit": 0.0, "debit": 0.0},
            {"id": 2, "name": "Friend 2", "credit": 0.0, "debit": 0.0},
            {"id": 3, "name": "Friend 3", "credit": 0.0, "debit": 0.0},
            {"id": 4, "name": "Friend 4", "credit": 0.0, "debit": 0.0},
        ]
        self.update_friends_list()

    def update_friends_list(self):
        """Actualiza la visualización de la lista de amigos"""
        # Limpiar lista actual
        child = self.friends_box.get_first_child()
        while child:
            next_child = child.get_next_sibling()
            self.friends_box.remove(child)
            child = next_child

        # Añadir amigos
        for friend in self._friends_data:
            friend_row = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=10)
            friend_row.add_css_class("friend-row")
            
            name_label = Gtk.Label(label=friend["name"])
            name_label.set_hexpand(True)
            name_label.set_halign(Gtk.Align.START)

            expense_btn = Gtk.Button(label="Expense list")
            expense_btn.connect("clicked", self.show_friend_expenses, friend)
            
            friend_row.append(name_label)
            friend_row.append(expense_btn)
            self.friends_box.append(friend_row)

    def on_edit_friend_ok(self, button, dialog, name_entry, credit_entry, debit_entry):
        """Confirma edición de amigo"""
        if self.selected_friend:
            self.selected_friend["name"] = name_entry.get_text().strip()
            try:
                self.selected_friend["credit"] = float(credit_entry.get_text())
                self.selected_friend["debit"] = float(debit_entry.get_text())
            except ValueError:
                pass
            self.update_friends_list()
        dialog.close()

    def on_remove_friend(self, button, dialog):
        """Elimina amigo"""
        if self.selected_friend:
            self._friends_data = [f for f in self._friends_data if f["id"] != self.selected_friend["id"]]
            self.update_friends_list()
        dialog.close()

    def on_show_list_clicked(self, button):
        """Muestra lista detallada de amigos"""
        dialog = Gtk.Dialog(title="Split - Amigos - Lista")
        dialog.set_transient_for(self.get_root())
        dialog.set_modal(True)
        dialog.set_default_size(500, 400)

        content = dialog.get_content_area()
        content.set_spacing(10)

        # Lista de amigos con gastos
        for friend in self._friends_data:
            friend_box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL, spacing=10)
            friend_box.set_margin_top(5)
            friend_box.set_margin_bottom(5)
            friend_box.set_margin_start(10)
            friend_box.set_margin_end(10)
            
            name_label = Gtk.Label(label=friend["name"])
            name_label.set_hexpand(True)
            name_label.set_halign(Gtk.Align.START)
            
            expense_btn = Gtk.Button(label="Expense list")
            expense_btn.connect("clicked", self.show_friend_expenses, friend)
            
            friend_box.append(name_label)
            friend_box.append(expense_btn)
            content.append(friend_box)

        # Botón cerrar
        close_btn = Gtk.Button(label="Close")
        close_btn.connect("clicked", lambda b: dialog.close())
        #close_btn.set_halign(Gtk.Align.CENTER)
        close_btn.set_margin_start(10)
        close_btn.set_margin_end(10)
        content.append(close_btn)

        dialog.show()

    def show_friend_expenses(self, button, friend):
        """Muestra gastos de un amigo específico"""
        dialog = Gtk.Dialog(title="Split - Amigos - Gastos por amigo")
        dialog.set_transient_for(self.get_root())
        dialog.set_modal(True)
        dialog.set_default_size(400, 300)

        content = dialog.get_content_area()
        content.set_spacing(10)

        # Lista de gastos simulada
        expenses = ["Expense 1", "Expense 2", "Expense 3", "Expense 4"]
        
        for expense in expenses:
            #expense_box = Gtk.Box(orientation=Gtk.Orientation.HORIZONTAL)
            
            expense_label = Gtk.Label(label=expense)
            # expense_label.set_margin_start(10)
            
            balance_label = Gtk.Label(label="+/- XXXXXXXXXX")
            balance_btn = Gtk.Button(label="Change balance")

            balance_btn.set_margin_start(10)
            balance_btn.set_margin_end(10)
            balance_btn.set_margin_top(10)
            # balance_btn.set_halign(Gtk.Align.END)

            # balance_label.set_margin_end(10)

            content.append(expense_label)
            content.append(balance_label)
            content.append(balance_btn)

        # Botón cerrar
        close_btn = Gtk.Button(label="Close")
        close_btn.connect("clicked", lambda b: dialog.close())
        # close_btn.set_halign(Gtk.Align.END)
        close_btn.set_margin_start(10)
        close_btn.set_margin_end(10)
        content.append(close_btn)

        dialog.show()
