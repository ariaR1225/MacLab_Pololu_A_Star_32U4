import sys
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QPushButton, QLineEdit, QVBoxLayout, QComboBox
from PyQt5.QtGui import QPixmap

class ImageWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        # Set window properties
        self.setGeometry(300, 300, 350, 300)
        self.setWindowTitle('PyQt5 Image with Widgets')

        # Create a vertical layout
        layout = QVBoxLayout()

        # Create a label to display the image
        label = QLabel(self)
        pixmap = QPixmap(r'/Users/ariar/Desktop/Screenshot 2023-12-03 at 18.52.00.png')  # Replace with your image path
        label.setPixmap(pixmap)
        layout.addWidget(label)

        # Create a QLineEdit widget
        self.lineEdit = QLineEdit(self)
        layout.addWidget(self.lineEdit)

        # Create a QComboBox widget
        self.comboBox = QComboBox(self)
        self.comboBox.addItems(["Option 1", "Option 2", "Option 3"])  # Add your options here
        layout.addWidget(self.comboBox)

        # Create a QPushButton and connect it to a function
        button = QPushButton('Print Value', self)
        button.clicked.connect(self.on_click)
        layout.addWidget(button)

        # Set the layout
        self.setLayout(layout)
        self.resize(pixmap.width(), pixmap.height() + 150)  # Adjust height for additional widgets

    def on_click(self):
        # Print the value from the line edit and combo box widgets
        print("Text:", self.lineEdit.text())
        print("Selected Option:", self.comboBox.currentText())

app = QApplication([])
ex = ImageWindow()
ex.show()
app.exec_()
