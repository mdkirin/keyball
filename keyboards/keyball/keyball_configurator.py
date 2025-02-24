import sys
from PyQt6.QtWidgets import (QApplication, QMainWindow, QWidget, QVBoxLayout, 
                            QHBoxLayout, QTabWidget, QPushButton, QLabel, 
                            QLineEdit, QComboBox, QGridLayout, QDockWidget,
                            QListWidget, QDialog, QMessageBox)
from PyQt6.QtCore import Qt, QMimeData
from PyQt6.QtGui import QDrag, QPainter, QColor

class KeycodeButton(QPushButton):
    def __init__(self, keycode="", display_name="", parent=None):
        super().__init__(display_name or keycode, parent)
        self.keycode = keycode
        self.display_name = display_name or keycode
        self.setFixedSize(60, 60)
        self.setAcceptDrops(True)
        self.setStyleSheet("""
            QPushButton {
                background-color: #2a2a2a;
                color: #ffffff;
                border: 1px solid #3a3a3a;
                border-radius: 5px;
                font-size: 12px;
            }
            QPushButton:hover {
                background-color: #3a3a3a;
            }
        """)

    def mousePressEvent(self, e):
        if e.button() == Qt.MouseButton.LeftButton:
            drag = QDrag(self)
            mime = QMimeData()
            mime.setText(self.keycode)
            drag.setMimeData(mime)
            drag.exec()

    def dragEnterEvent(self, e):
        e.accept()

    def dropEvent(self, e):
        new_keycode = e.mimeData().text()
        self.keycode = new_keycode
        self.setText(new_keycode)
        e.accept()

class KeycodePalette(QDockWidget):
    def __init__(self, parent=None):
        super().__init__("Keycodes", parent)
        self.setFeatures(QDockWidget.DockWidgetFeature.DockWidgetFloatable |
                        QDockWidget.DockWidgetFeature.DockWidgetMovable)
        
        # 키코드 카테고리
        widget = QWidget()
        layout = QVBoxLayout()
        
        # 카테고리 선택
        self.category_combo = QComboBox()
        self.category_combo.addItems([
            "Basic",
            "Modifiers",
            "Layers",
            "Special",
            "Media",
            "Mouse"
        ])
        self.category_combo.currentTextChanged.connect(self.update_keycodes)
        layout.addWidget(self.category_combo)
        
        # 키코드 그리드
        self.keycode_grid = QGridLayout()
        self.update_keycodes("Basic")
        
        layout.addLayout(self.keycode_grid)
        widget.setLayout(layout)
        self.setWidget(widget)

    def update_keycodes(self, category):
        # 기존 키코드 제거
        while self.keycode_grid.count():
            item = self.keycode_grid.takeAt(0)
            if item.widget():
                item.widget().deleteLater()

        # 카테고리별 키코드
        keycodes = {
            "Basic": [
                ("KC_A", "A"), ("KC_B", "B"), ("KC_C", "C"),
                ("KC_1", "1"), ("KC_2", "2"), ("KC_3", "3")
            ],
            "Modifiers": [
                ("KC_LCTL", "LCtrl"), ("KC_LSFT", "LShift"),
                ("KC_LALT", "LAlt"), ("KC_LGUI", "LGUI")
            ],
            "Layers": [
                ("MO(1)", "MO 1"), ("MO(2)", "MO 2"),
                ("TO(1)", "TO 1"), ("TO(2)", "TO 2")
            ]
        }

        # 선택된 카테고리의 키코드 표시
        codes = keycodes.get(category, [])
        row = 0
        col = 0
        for code, display in codes:
            btn = KeycodeButton(code, display)
            self.keycode_grid.addWidget(btn, row, col)
            col += 1
            if col > 3:
                col = 0
                row += 1

class KeyboardLayout(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        layout = QVBoxLayout()
        
        # 키보드 레이아웃 그리드
        keyboard = QGridLayout()
        keyboard.setSpacing(5)
        
        # Keyball39 레이아웃
        self.create_keyboard_layout(keyboard)
        
        layout.addLayout(keyboard)
        self.setLayout(layout)

    def create_keyboard_layout(self, grid):
        # 기본 레이어 키 배치
        layout = [
            ['KC_Q', 'KC_W', 'KC_E', 'KC_R', 'KC_T', None, 'KC_Y', 'KC_U', 'KC_I', 'KC_O', 'KC_P'],
            ['KC_A', 'KC_S', 'KC_D', 'KC_F', 'KC_G', None, 'KC_H', 'KC_J', 'KC_K', 'KC_L', 'KC_ENT'],
            ['KC_Z', 'KC_X', 'KC_C', 'KC_V', 'KC_B', None, 'KC_N', 'KC_M', 'KC_COMM', 'KC_DOT', 'KC_SLSH'],
            ['KC_LCTL', 'KC_LGUI', 'KC_LALT', 'KC_LNG2', 'MO(1)', 'MO(3)', 'KC_SPC', 'MO(2)', 'KC_LNG2', 'KC_RALT', 'KC_RGUI', 'KC_RCTL']
        ]

        for row, keys in enumerate(layout):
            for col, key in enumerate(keys):
                if key:
                    btn = KeycodeButton(key)
                    grid.addWidget(btn, row, col)

class ComboEditor(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("Combo Editor")
        layout = QVBoxLayout()
        
        # 콤보 리스트
        self.combo_list = QListWidget()
        layout.addWidget(self.combo_list)
        
        # 콤보 추가/제거 버튼
        btn_layout = QHBoxLayout()
        add_btn = QPushButton("Add Combo")
        remove_btn = QPushButton("Remove Combo")
        btn_layout.addWidget(add_btn)
        btn_layout.addWidget(remove_btn)
        layout.addLayout(btn_layout)
        
        self.setLayout(layout)

class KeyOverrideEditor(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("Key Override Editor")
        self.setMinimumWidth(600)
        layout = QVBoxLayout()
        
        # 오버라이드 리스트
        self.override_list = QListWidget()
        layout.addWidget(QLabel("Key Overrides:"))
        layout.addWidget(self.override_list)
        
        # 오버라이드 설정
        form_layout = QGridLayout()
        
        # 트리거 키 설정
        form_layout.addWidget(QLabel("Trigger Key:"), 0, 0)
        self.trigger_key = QComboBox()
        self.trigger_key.addItems(["KC_A", "KC_B", "KC_C", "KC_1", "KC_2", "KC_3"])
        form_layout.addWidget(self.trigger_key, 0, 1)
        
        # 모디파이어 설정
        form_layout.addWidget(QLabel("Modifiers:"), 1, 0)
        self.mod_layout = QHBoxLayout()
        self.mod_ctrl = QPushButton("Ctrl")
        self.mod_shift = QPushButton("Shift")
        self.mod_alt = QPushButton("Alt")
        self.mod_gui = QPushButton("GUI")
        
        for btn in [self.mod_ctrl, self.mod_shift, self.mod_alt, self.mod_gui]:
            btn.setCheckable(True)
            self.mod_layout.addWidget(btn)
        
        form_layout.addLayout(self.mod_layout, 1, 1)
        
        # 대체 키 설정
        form_layout.addWidget(QLabel("Replacement Key:"), 2, 0)
        self.replacement_key = QComboBox()
        self.replacement_key.addItems(["KC_A", "KC_B", "KC_C", "KC_1", "KC_2", "KC_3"])
        form_layout.addWidget(self.replacement_key, 2, 1)
        
        # 옵션 설정
        form_layout.addWidget(QLabel("Options:"), 3, 0)
        self.option_layout = QHBoxLayout()
        self.opt_activation = QComboBox()
        self.opt_activation.addItems(["Activate on Press", "Activate on Hold", "Activate on Tap"])
        self.option_layout.addWidget(self.opt_activation)
        form_layout.addLayout(self.option_layout, 3, 1)
        
        layout.addLayout(form_layout)
        
        # 버튼들
        btn_layout = QHBoxLayout()
        add_btn = QPushButton("Add Override")
        remove_btn = QPushButton("Remove Override")
        add_btn.clicked.connect(self.add_override)
        remove_btn.clicked.connect(self.remove_override)
        
        btn_layout.addWidget(add_btn)
        btn_layout.addWidget(remove_btn)
        layout.addLayout(btn_layout)
        
        self.setLayout(layout)
    
    def add_override(self):
        trigger = self.trigger_key.currentText()
        mods = []
        if self.mod_ctrl.isChecked(): mods.append("Ctrl")
        if self.mod_shift.isChecked(): mods.append("Shift")
        if self.mod_alt.isChecked(): mods.append("Alt")
        if self.mod_gui.isChecked(): mods.append("GUI")
        replacement = self.replacement_key.currentText()
        activation = self.opt_activation.currentText()
        
        override_text = f"{trigger} + {'+'.join(mods)} → {replacement} ({activation})"
        self.override_list.addItem(override_text)
    
    def remove_override(self):
        current = self.override_list.currentRow()
        if current >= 0:
            self.override_list.takeItem(current)

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Keyball39 Configurator")
        self.setGeometry(100, 100, 1400, 800)
        
        # 메인 위젯
        main_widget = QWidget()
        self.setCentralWidget(main_widget)
        layout = QVBoxLayout()
        
        # 레이어 탭
        tabs = QTabWidget()
        for layer in ["Base", "Function", "Numpad", "Ball", "Media"]:
            tabs.addTab(KeyboardLayout(), layer)
        layout.addWidget(tabs)
        
        # 키코드 팔레트
        self.keycode_palette = KeycodePalette(self)
        self.addDockWidget(Qt.DockWidgetArea.RightDockWidget, self.keycode_palette)
        
        # 하단 버튼
        btn_layout = QHBoxLayout()
        save_btn = QPushButton("Save Keymap")
        combo_btn = QPushButton("Edit Combos")
        homerow_btn = QPushButton("Home Row Settings")
        override_btn = QPushButton("Key Overrides")
        
        save_btn.clicked.connect(self.save_keymap)
        combo_btn.clicked.connect(self.edit_combos)
        homerow_btn.clicked.connect(self.edit_homerow)
        override_btn.clicked.connect(self.edit_overrides)
        
        btn_layout.addWidget(save_btn)
        btn_layout.addWidget(combo_btn)
        btn_layout.addWidget(homerow_btn)
        btn_layout.addWidget(override_btn)
        layout.addLayout(btn_layout)
        
        main_widget.setLayout(layout)

    def save_keymap(self):
        # TODO: 키맵 파일 생성 구현
        QMessageBox.information(self, "Save", "Keymap files will be generated")

    def edit_combos(self):
        dialog = ComboEditor(self)
        dialog.exec()

    def edit_homerow(self):
        # TODO: 홈로우 설정 다이얼로그 구현
        pass

    def edit_overrides(self):
        dialog = KeyOverrideEditor(self)
        dialog.exec()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    app.setStyle('Fusion')  # 다크 테마에 적합한 스타일
    window = MainWindow()
    window.show()
    sys.exit(app.exec()) 