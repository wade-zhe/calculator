#include "calculator.h"
#include <QVBoxLayout>

Calculator::Calculator(QWidget *parent) : QWidget(parent), waitingForOperand(false) {
    // Setup main layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Setup display
    display = new QLineEdit("0", this);
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    mainLayout->addWidget(display);

    // Setup buttons grid
    QGridLayout *gridLayout = new QGridLayout();

    // Create number buttons
    QString digits[] = {"7", "8", "9", "4", "5", "6", "1", "2", "3", "0"};
    int pos = 0;
    for (int row = 1; row <= 4; row++) {
        for (int col = 0; col < 3 && pos < 10; col++) {
            if (row == 4 && col == 0) continue; // Skip for '0'
            createButton(digits[pos], gridLayout, row, col);
            pos++;
        }
    }
    createButton("0", gridLayout, 4, 0); // Place '0' button

    // Create operator buttons
    createButton("+", gridLayout, 1, 3);
    createButton("-", gridLayout, 2, 3);
    createButton("*", gridLayout, 3, 3);
    createButton("/", gridLayout, 4, 3);

    // Create control buttons
    createButton("C", gridLayout, 0, 0);
    createButton("=", gridLayout, 4, 2);

    mainLayout->addLayout(gridLayout);
    setLayout(mainLayout);

    // Connect clear button
    connect(findChild<QPushButton*>("C"), &QPushButton::clicked, this, &Calculator::onClearClicked);

    // Initialize state
    onClearClicked();
}

void Calculator::createButton(const QString &text, QGridLayout *layout, int row, int col) {
    QPushButton *button = new QPushButton(text, this);
    button->setObjectName(text);
    layout->addWidget(button, row, col);

    if (text >= "0" && text <= "9") {
        connect(button, &QPushButton::clicked, this, &Calculator::onDigitClicked);
    } else if (text == "+" || text == "-" || text == "*" || text == "/") {
        connect(button, &QPushButton::clicked, this, &Calculator::onOperatorClicked);
    } else if (text == "=") {
        connect(button, &QPushButton::clicked, this, &Calculator::onEqualClicked);
    }
}

void Calculator::onDigitClicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString digit = button->text();

    if (waitingForOperand) {
        currentInput = digit;
        waitingForOperand = false;
    } else {
        currentInput = (currentInput == "0") ? digit : currentInput + digit;
    }

    display->setText(currentInput);
}

void Calculator::onOperatorClicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString newOperator = button->text();

    if (!currentInput.isEmpty()) {
        operand1 = currentInput;
        currentOperator = newOperator;
        waitingForOperand = true;
    }
}

void Calculator::onClearClicked() {
    currentInput = "0";
    operand1.clear();
    operand2.clear();
    currentOperator.clear();
    waitingForOperand = false;
    display->setText("0");
}

void Calculator::onEqualClicked() {
    if (currentInput.isEmpty() || operand1.isEmpty() || currentOperator.isEmpty())
        return;

    operand2 = currentInput;

    double result = 0.0;
    double op1 = operand1.toDouble();
    double op2 = operand2.toDouble();

    if (currentOperator == "+") result = op1 + op2;
    else if (currentOperator == "-") result = op1 - op2;
    else if (currentOperator == "*") result = op1 * op2;
    else if (currentOperator == "/") {
        if (op2 != 0) result = op1 / op2;
        else {
            display->setText("Error");
            return;
        }
    }

    currentInput = QString::number(result);
    display->setText(currentInput);
    operand1.clear();
    operand2.clear();
    currentOperator.clear();
    waitingForOperand = true;
}
