import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget, QVBoxLayout, QLineEdit, QLabel, QPushButton


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Certificate Polynomial Roots")
        self.resize(500, 500)

        # Create a central widget and set it as the main window's central widget
        central_widget = QWidget()
        self.setCentralWidget(central_widget)

        # Create a layout for the central widget
        self.layout = QVBoxLayout(central_widget)

        # Create a label and input field for the number of input boxes
        label = QLabel("Enter the degree of the polynomial:")
        self.layout.addWidget(label)

        self.num_input_field = QLineEdit()
        self.layout.addWidget(self.num_input_field)

        button = QPushButton("Continue")
        self.layout.addWidget(button)

        # Connect the button's clicked signal to a function
        button.clicked.connect(self.create_input_boxes)

        self.show()

    def create_input_boxes(self):
        num_input_boxes = self.num_input_field.text()

        try:
            num_input_boxes = int(num_input_boxes)
            if num_input_boxes < 0:
                raise ValueError
        except ValueError:
            print("Please enter a valid positive integer.")
            return

        # Clear the layout
        while self.layout.count():
            child = self.layout.takeAt(0)
            if child.widget():
                child.widget().deleteLater()

        # Create input boxes dynamically based on the input value
        for i in range(num_input_boxes):
            label = QLabel(f"Coefficient {i+1}:")
            self.layout.addWidget(label)

            input_field = QLineEdit()
            self.layout.addWidget(input_field)

        # Add a button to retrieve input values
        retrieve_button = QPushButton("Draw Gerschgorin Circles")
        self.layout.addWidget(retrieve_button)
        retrieve_button.clicked.connect(self.retrieve_input_values)

        # Add a "Go Back" button
        go_back_button = QPushButton("Go Back")
        self.layout.addWidget(go_back_button)
        go_back_button.clicked.connect(self.go_back)

    def retrieve_input_values(self):
        input_values = []
        for i in range(self.layout.count()):
            widget = self.layout.itemAt(i).widget()
            if isinstance(widget, QLineEdit):
                input_values.append(widget.text())

        print("Input Values:", input_values)

    def go_back(self):
        # Clear the layout
        while self.layout.count():
            child = self.layout.takeAt(0)
            if child.widget():
                child.widget().deleteLater()

        # Recreate the initial layout
        label = QLabel("Enter the number of input boxes:")
        self.layout.addWidget(label)

        self.num_input_field = QLineEdit()
        self.layout.addWidget(self.num_input_field)

        button = QPushButton("Create Input Boxes")
        self.layout.addWidget(button)

        # Connect the button's clicked signal to a function
        button.clicked.connect(self.create_input_boxes)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    sys.exit(app.exec_())
