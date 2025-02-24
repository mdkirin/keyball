import sys
from PyQt6.QtWidgets import (QApplication, QMainWindow, QWidget, QVBoxLayout, 
                            QHBoxLayout, QTabWidget, QPushButton, QLabel, 
                            QLineEdit, QComboBox, QGridLayout)
from PyQt6.QtCore import Qt

class KeyButton(QPushButton):
    def __init__(self, key="", parent=None):
        super().__init__(key, parent)
        self.key = key
        self.setFixedSize(60, 60)
        self.setStyleSheet("""
            QPushButton {
                background-color: #f0f0f0;
                border: 1px solid #ccc;
                border-radius: 5px;
            }
            QPushButton:hover {
                background-color: #e0e0e0;
            }
        """)

class LayerTab(QWidget):
    def __init__(self, layer_name, parent=None):
        super().__init__(parent)
        self.layer_name = layer_name
        layout = QVBoxLayout()
        
        # 키보드 레이아웃
        keyboard = QGridLayout()
        
        # 첫 번째 행 (숫자 키)
        for i, key in enumerate(['Q', 'W', 'E', 'R', 'T', '', 'Y', 'U', 'I', 'O', 'P']):
            if key:
                btn = KeyButton(key)
                keyboard.addWidget(btn, 0, i)
        
        # 두 번째 행 (홈로우)
        home_row = ['A', 'S', 'D', 'F', 'G', '', 'H', 'J', 'K', 'L', 'ENT']
        for i, key in enumerate(home_row):
            if key:
                btn = KeyButton(key)
                keyboard.addWidget(btn, 1, i)
        
        # 세 번째 행
        for i, key in enumerate(['Z', 'X', 'C', 'V', 'B', '', 'N', 'M', ',', '.', '/']):
            if key:
                btn = KeyButton(key)
                keyboard.addWidget(btn, 2, i)
        
        # 네 번째 행 (하단 키)
        bottom_row = ['Ctrl', 'GUI', 'Alt', 'LNG2', 'BSP', 'LNG1', 'SPC', 'ENT', 'LNG2', 'Alt', 'GUI', 'Ctrl']
        for i, key in enumerate(bottom_row):
            btn = KeyButton(key)
            keyboard.addWidget(btn, 3, i)
        
        layout.addLayout(keyboard)
        self.setLayout(layout)

class KeymapEditor(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Keyball39 Keymap Editor")
        self.setGeometry(100, 100, 1200, 800)
        
        # 메인 위젯과 레이아웃
        main_widget = QWidget()
        self.setCentralWidget(main_widget)
        layout = QVBoxLayout()
        
        # 탭 위젯 생성
        tabs = QTabWidget()
        tabs.addTab(LayerTab("Base"), "Base Layer")
        tabs.addTab(LayerTab("Function"), "Function Layer")
        tabs.addTab(LayerTab("Numpad"), "Numpad Layer")
        tabs.addTab(LayerTab("Ball"), "Ball Layer")
        tabs.addTab(LayerTab("Media"), "Media Layer")
        
        # 설정 버튼들
        buttons_layout = QHBoxLayout()
        save_button = QPushButton("Save Keymap")
        save_button.clicked.connect(self.save_keymap)
        compile_button = QPushButton("Compile")
        compile_button.clicked.connect(self.compile_firmware)
        
        buttons_layout.addWidget(save_button)
        buttons_layout.addWidget(compile_button)
        
        layout.addWidget(tabs)
        layout.addLayout(buttons_layout)
        main_widget.setLayout(layout)
    
    def save_keymap(self):
        # TODO: 키맵 파일 저장 구현
        pass
    
    def compile_firmware(self):
        # TODO: QMK 컴파일 구현
        pass

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = KeymapEditor()
    window.show()
    sys.exit(app.exec()) 