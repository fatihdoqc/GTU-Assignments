import numpy as np
from math import fabs
import matplotlib.pyplot as plt
import numpy.polynomial
from numpy import linalg as LA
import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget, QVBoxLayout, QLineEdit, QLabel, QPushButton
from PyQt5.QtGui import QPixmap

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
        label = QLabel("Enter the input number for the polynomial (Degree + 1) :")
        self.layout.addWidget(label)

        self.num_input_field = QLineEdit()
        self.layout.addWidget(self.num_input_field)

        button = QPushButton("Continue")
        self.layout.addWidget(button)

        # Connect the button's clicked signal to a function
        button.clicked.connect(self.create_input_boxes)

        self.input_values = []
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
        self.input_values.clear()
        for i in range(self.layout.count()):
            widget = self.layout.itemAt(i).widget()
            if isinstance(widget, QLineEdit):
                self.input_values.append(widget.text())

        print("Input Values:", self.input_values)

        self.show_polynomial_and_png()

    def go_back(self):
        # Clear the layout
        while self.layout.count():
            child = self.layout.takeAt(0)
            if child.widget():
                child.widget().deleteLater()

        # Recreate the initial layout
        label = QLabel("Enter the input number for the polynomial (Degree + 1) :")
        self.layout.addWidget(label)

        self.num_input_field = QLineEdit()
        self.layout.addWidget(self.num_input_field)

        button = QPushButton("Continue")
        self.layout.addWidget(button)

        # Connect the button's clicked signal to a function
        button.clicked.connect(self.create_input_boxes)

    def show_polynomial_and_png(self):
        # Clear the layout
        while self.layout.count():
            child = self.layout.takeAt(0)
            if child.widget():
                child.widget().deleteLater()

        degree = len(self.input_values) - 1

        # Create the polynomial string representation
        polynomial_str = "Polynomial: "
        for i, coeff in enumerate(self.input_values):

            if degree == i:
                polynomial_str += coeff
            else:
                polynomial_str += f"{coeff}x^{degree - i} + " if degree - i > 1 else f"{coeff}x + "
        polynomial_str = polynomial_str.rstrip(" + ")

        pol = []
        for element in self.input_values:
            pol.append(int(element))

        companionMatrix = CompanionPolynomial(pol)
        w,v = LA.eig(companionMatrix)

        easy_roots = np.roots(self.input_values)
        print(easy_roots)

        real_roots = []
        for x in easy_roots:
            if(numpy.iscomplex(x)):
                print('Root is not real')
            else:
                real_roots.append(x)

        if not real_roots:
            print('There is no real root of this polynomial')
            message = QLabel('There is no real root of this polynomial')
            self.layout.addWidget(message)

        else:
            expected_roots = ("Expected roots: ")
            for x in w:
                if not numpy.iscomplex(x):
                    expected_roots += str(x) + ', '

            exp_roots = QLabel(expected_roots)
            self.layout.addWidget(exp_roots)

            test = GregsCircles(companionMatrix)
            plotCircles(test, w)

            # Create the QLabel with the polynomial string representation
            label = QLabel(polynomial_str)
            self.layout.addWidget(label)

            pixmap = QPixmap("plotcircles.png")
            image_label = QLabel()
            image_label.setPixmap(pixmap)
            self.layout.addWidget(image_label)

            # Add a "Go Back" button
            go_back_button = QPushButton("Go Back")
            self.layout.addWidget(go_back_button)
            go_back_button.clicked.connect(self.go_back)

def CompanionPolynomial(polynomial):
    for x in polynomial:
        if not np.isreal(x):
            print('Polynomial is not real.')
            return []

    degree = len(polynomial) - 1
    matrix = np.zeros((degree,degree))

    for x in range(degree):
        if (x == 0) :
            matrix[x, degree-1] = - (polynomial[degree] / polynomial[0]) # first row
            continue

        matrix[x, x-1] = 1 # Placing 1's starting from second row
        matrix[x, degree - 1] = - (polynomial[degree - x] / polynomial[0])

    return matrix

def GregsCircles(matrix):
    if isSquare(matrix) != True:
        print('Your input matrix is not square!')
        return []

    circles = []
    for x in range(0,len(matrix)):
        radius = 0
        piv = matrix[x][x]

        for y in range(0,len(matrix)):
            if x != y:
                radius += fabs(matrix[x][y])

        circles.append([piv,radius])

    return circles

def plotCircles(circles, roots):
    index, radi = zip(*circles)

    Xupper = max(radi) + np.std(index)
    Xlower = -(max(radi) + np.std(index))
    Ylimit = max(radi) + np.std(index)

    fig, ax = plt.subplots()
    ax = plt.gca()
    ax.cla()
    ax.set_xlim((Xlower,Xupper))
    ax.set_ylim((-Ylimit,Ylimit))

    for root in roots:
        if not numpy.iscomplex(root):
            ax.scatter(root, 0, color='blue')
            plt.plot([root], linestyle='dashed')
            plt.plot([root, root], [-Ylimit, 0], linestyle='dashed', color='black')

    plt.xlabel('Real Axis')
    plt.ylabel('Imaginary Axis')
    plt.title('Gerschgorin circles')

    for x in range(0,len(circles)):
        circ = plt.Circle((index[x],0), radius = radi[x], color='red' , alpha=0.2)
        print(index[x])
        #plt.plot(x_points, y_points, linestyle='dashed')
        ax.add_artist(circ)

    ax.plot([Xlower,Xupper],[0,0],'k--')
    ax.plot([0,0],[-Ylimit,Ylimit],'k--')

    fig.savefig('plotcircles.png')
    plt.show()

def isSquare(m):
    cols = len(m)

    for row in m:
        if len(row) != cols:
            return False

    return True

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    sys.exit(app.exec_())

# x^3 - 5x^2 + 2x + 8
# polynomial = [1 , -5, 2, 8]
# companionMatrix = CompanionPolynomial(polynomial)
# w,v = LA.eig(companionMatrix)
# print(companionMatrix)
#
# print('evals: ', w) #eigenvalues
# print('numpy pol roots:' , np.roots(polynomial))
#
# # matrix = [ [10,-1,0,1] , [0.2,8,0.2,0.2], [1,1,2,1] , [-1,-1,-1,-11]]
# test = GregsCircles(companionMatrix)
# plotCircles(test,w)