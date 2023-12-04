import sys
from PyQt5.QtWidgets import (QApplication, QWidget, QLabel, QPushButton, QLineEdit, QVBoxLayout, QHBoxLayout,
                             QComboBox, QCheckBox, QSizePolicy)
from PyQt5.QtGui import QPixmap, QPainter
from PyQt5.QtCore import Qt

file_path = r"/Users/ariar/Documents/GitHub/MacLab_Pololu_A_Star_32U4/GUI/"

class ImageWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.d0x = 450
        self.d0y = 240
        self.d1x = 80
        self.d1y = 240
        self.d2x = 90
        self.d2y = 210
        self.d3x = 440
        self.d3y = 200
        self.f1x = 35
        self.f1y = 240
        self.f2x = 500
        self.f2y = 230
        self.subject_name = "XXX"

        # Set window properties
        self.setGeometry(300, 300, 350, 300)
        self.setWindowTitle('Cell World GUI')

        # Create a vertical layout with reduced spacing and margins
        layout = QVBoxLayout()
        layout.setSpacing(5)
        layout.setContentsMargins(5, 5, 5, 5)

        # Create a label to display the image
        self.imageLabel = QLabel(self)
        self.defaultPixmap = QPixmap(file_path + 'habitat.png').scaled(600, 400, Qt.KeepAspectRatio)
        self.alternatePixmap = QPixmap(file_path + 'test1.png').scaled(50, 50, Qt.KeepAspectRatio)
        self.openPixmap = QPixmap(file_path + 'open.png').scaled(50, 50, Qt.KeepAspectRatio)
        self.closePixmap = QPixmap(file_path + 'close.png').scaled(50, 50, Qt.KeepAspectRatio)
        self.testPixmap = QPixmap(file_path + 'test.png').scaled(50, 50, Qt.KeepAspectRatio)

        self.imageLabel.setPixmap(self.defaultPixmap)
        layout.addWidget(self.imageLabel)

        # Open Door
        OpenDoorsLayout = QHBoxLayout()
        self.door0 = QCheckBox("door 0", self)
        self.door1 = QCheckBox("door 1", self)
        self.door2 = QCheckBox("door 2", self)
        self.door3 = QCheckBox("door 3", self)
        OpenDoorsLayout.addWidget(self.door0)
        OpenDoorsLayout.addWidget(self.door1)
        OpenDoorsLayout.addWidget(self.door2)
        OpenDoorsLayout.addWidget(self.door3)
        OpenDoorbutton = QPushButton('Open/Close Door', self)
        OpenDoorbutton.clicked.connect(self.OpenDoor)
        OpenDoorsLayout.addWidget(OpenDoorbutton)
        layout.addLayout(OpenDoorsLayout)

        # Test Door
        TestDoorLayout = QHBoxLayout()

        self.TestDoorCombobox = QComboBox(self)
        self.TestDoorCombobox.addItems(["door 0", "door 1", "door 2", "door 3"])
        TestDoorLayout.addWidget(self.TestDoorCombobox)

        DoorTimeTextLabel = QLabel("Time (s)", self)
        TestDoorLayout.addWidget(DoorTimeTextLabel)

        self.DoorTimeTextEntry = QLineEdit(self)
        TestDoorLayout.addWidget(self.DoorTimeTextEntry)

        DoorRepTextLabel = QLabel("Rep", self)
        TestDoorLayout.addWidget(DoorRepTextLabel)

        self.DoorRepTextEntry = QLineEdit(self)
        TestDoorLayout.addWidget(self.DoorRepTextEntry)

        TestDoorButton = QPushButton('Test Door', self)
        TestDoorButton.clicked.connect(self.TestDoor)
        TestDoorLayout.addWidget(TestDoorButton)

        layout.addLayout(TestDoorLayout)

        # Test Feeder
        TestFeederLayout = QHBoxLayout()
        self.TestFeederCombobox = QComboBox(self)
        self.TestFeederCombobox.addItems(["feeder 1", "feeder 2"])
        TestFeederLayout.addWidget(self.TestFeederCombobox)

        FeederTimeTextLabel = QLabel("Time (s)", self)
        TestFeederLayout.addWidget(FeederTimeTextLabel)

        self.FeederTimeEntry = QLineEdit(self)
        TestFeederLayout.addWidget(self.FeederTimeEntry)

        FeederRepTextLabel = QLabel("Rep", self)
        TestFeederLayout.addWidget(FeederRepTextLabel)

        self.FeederRepEntry = QLineEdit(self)
        TestFeederLayout.addWidget(self.FeederRepEntry)

        FeederWaitTextLabel = QLabel("Wait (s)", self)
        TestFeederLayout.addWidget(FeederWaitTextLabel)

        self.FeederWaitEntry = QLineEdit(self)
        TestFeederLayout.addWidget(self.FeederWaitEntry)

        TestFeederButton = QPushButton('Test Feeder', self)
        TestFeederButton.clicked.connect(self.TestFeeder)
        TestFeederLayout.addWidget(TestFeederButton)

        layout.addLayout(TestFeederLayout)

        # Experiment Name
        ExpLayout = QHBoxLayout()

        ExpPreTextLabel = QLabel("Prefix (s)", self)
        ExpLayout.addWidget(ExpPreTextLabel)

        self.ExpPreEntry = QLineEdit(self)
        self.ExpPreEntry.setText("PEEK")
        ExpLayout.addWidget(self.ExpPreEntry)

        ExpSubLabel = QLabel("Subject Name", self)
        ExpLayout.addWidget(ExpSubLabel)

        self.ExpSubEntry = QLineEdit(self)
        ExpLayout.addWidget(self.ExpSubEntry)

        ExpSufTextLabel = QLabel("Suffix", self)
        ExpLayout.addWidget(ExpSufTextLabel)

        self.ExpCombobox = QComboBox(self)
        self.ExpCombobox.addItems(["RT", "CT", "HT"])
        ExpLayout.addWidget(self.ExpCombobox)

        layout.addLayout(ExpLayout)

        # Experiment Status
        ExpStaLayout = QHBoxLayout()

        StartButton = QPushButton('Start Experiment', self)
        StartButton.clicked.connect(self.StartExp)
        ExpStaLayout.addWidget(StartButton)

        FinishButton = QPushButton('Finish Experiment', self)
        FinishButton.clicked.connect(self.FinishExp)
        ExpStaLayout.addWidget(FinishButton)

        UploadButton = QPushButton('Upload Experiment', self)
        UploadButton.clicked.connect(self.UploadExp)
        ExpStaLayout.addWidget(UploadButton)

        layout.addLayout(ExpStaLayout)

        # Other
        FucLayout = QHBoxLayout()

        HelpButton = QPushButton('Help', self)
        HelpButton.clicked.connect(self.Help)
        FucLayout.addWidget(HelpButton)

        ConButton = QPushButton('(Re)Connect', self)
        ConButton.clicked.connect(self.Connect)
        FucLayout.addWidget(ConButton)

        layout.addLayout(FucLayout)

        # Set the layout
        self.setLayout(layout)
        self.resize(650, 550)
    
    def overlay(self, xpos, ypos, overlayImage):
        painter = QPainter(self.defaultPixmap)
        painter.drawPixmap(xpos, ypos, overlayImage)
        painter.end()
        self.imageLabel.setPixmap(self.defaultPixmap)
        self.update() 


    def OpenDoor(self):
        checked_options = []
        if self.door0.isChecked():
            checked_options.append(self.door0.text())
            self.overlay(self.d0x,self.d0y,self.openPixmap)
        else:
            self.overlay(self.d0x,self.d0y,self.closePixmap)

        if self.door1.isChecked():
            checked_options.append(self.door1.text())
            self.overlay(self.d1x,self.d1y,self.openPixmap)
        else:
            self.overlay(self.d1x,self.d1y,self.closePixmap)

        if self.door2.isChecked():
            checked_options.append(self.door2.text())
            self.overlay(self.d2x,self.d2y,self.openPixmap)
        else:
            self.overlay(self.d2x,self.d2y,self.closePixmap)

        if self.door3.isChecked():
            checked_options.append(self.door3.text())
            self.overlay(self.d3x,self.d3y,self.openPixmap)
        else:
            self.overlay(self.d3x,self.d3y,self.closePixmap)

        print("Checked Options:", ', '.join(checked_options) if checked_options else "None")

    def TestDoor(self):
        print("Door Num:", self.TestDoorCombobox.currentText())
        print("Time:", self.DoorTimeTextEntry.text())
        print("Rep:", self.DoorRepTextEntry.text())
    
    def TestFeeder(self):
        print("Feeder Num:", self.TestFeederCombobox.currentText())
        print("Time:", self.FeederTimeEntry.text())
        print("Rep:", self.FeederRepEntry.text())
        print("Rep:", self.FeederWaitEntry.text())

        if self.TestFeederCombobox.currentText() == "feeder 1":
            self.overlay(self.f1x,self.f1y,self.testPixmap)
        if self.TestFeederCombobox.currentText() == "feeder 2":
            self.overlay(self.f2x,self.f2y,self.testPixmap)
    
    def StartExp(self):
        self.subject_name = f"{self.ExpPreEntry.text()}_{self.ExpSubEntry.text()}_{self.ExpCombobox.currentText()}"
        
    def FinishExp(self):
        print(self.subject_name)

    def UploadExp(self):
        pass

    def Help(self):
        print("ALL COMMANDS")
    
    def Connect(self):
        print("Connecting ...")

app = QApplication([])
ex = ImageWindow()
ex.show()
app.exec_()
