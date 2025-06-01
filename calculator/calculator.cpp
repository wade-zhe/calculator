// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "calculator.h"
#include "button.h"

#include <QGridLayout>
#include <QLineEdit>
#include <QtMath>

//! [0]
Calculator::Calculator(QWidget *parent)
    : QWidget(parent), sumInMemory(0.0), sumSoFar(0.0)
    , factorSoFar(0.0), waitingForOperand(true)
    , baseForExponent(0.0), waitingForExponent(false)

{
    //! [0]

    //! [1]
    display = new QLineEdit("0");
    //! [1] //! [2]
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);

    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);
    //! [2]

    //! [4]
    for (int i = 0; i < NumDigitButtons; ++i)
        digitButtons[i] = createButton(QString::number(i), &Calculator::digitClicked);

    Button *pointButton = createButton(tr("."), &Calculator::pointClicked);
    Button *changeSignButton = createButton(tr("\302\261"), &Calculator::changeSignClicked);

    Button *backspaceButton = createButton(tr("Backspace"), &Calculator::backspaceClicked);
    Button *clearButton = createButton(tr("Clear"), &Calculator::clear);
    Button *clearAllButton = createButton(tr("Clear All"), &Calculator::clearAll);

    Button *clearMemoryButton = createButton(tr("MC"), &Calculator::clearMemory);
    Button *readMemoryButton = createButton(tr("MR"), &Calculator::readMemory);
    Button *setMemoryButton = createButton(tr("MS"), &Calculator::setMemory);
    Button *addToMemoryButton = createButton(tr("M+"), &Calculator::addToMemory);

    Button *divisionButton = createButton(tr("\303\267"), &Calculator::multiplicativeOperatorClicked);
    Button *timesButton = createButton(tr("\303\227"), &Calculator::multiplicativeOperatorClicked);
    Button *minusButton = createButton(tr("-"), &Calculator::additiveOperatorClicked);
    Button *plusButton = createButton(tr("+"), &Calculator::additiveOperatorClicked);

    Button *squareRootButton = createButton(tr("Sqrt"), &Calculator::unaryOperatorClicked);
    Button *powerButton = createButton(tr("x\302\262"), &Calculator::unaryOperatorClicked);
    Button *reciprocalButton = createButton(tr("1/x"), &Calculator::unaryOperatorClicked);
    Button *equalButton = createButton(tr("="), &Calculator::equalClicked);
    Button *toUSDButton = createButton(tr("NTD → USD"), &Calculator::convertToUSD);
    Button *toTWDButton = createButton(tr("USD → NTD"), &Calculator::convertToTWD);
    Button *sinButton = createButton(tr("sin"), &Calculator::unaryTrigOperatorClicked);
    Button *cosButton = createButton(tr("cos"), &Calculator::unaryTrigOperatorClicked);
    Button *tanButton = createButton(tr("tan"), &Calculator::unaryTrigOperatorClicked);
    Button *logButton = createButton(tr("log"), &Calculator::unaryLogOperatorClicked);
    Button *powerXYButton = createButton(tr("x^y"), &Calculator::powerXYClicked);


    Button *arcsinButton = createButton(tr("arcsin"), &Calculator::unaryARCTrigOperatorClicked);
    Button *arccosButton = createButton(tr("arccos"), &Calculator::unaryARCTrigOperatorClicked);
    Button *arctanButton = createButton(tr("arctan"), &Calculator::unaryARCTrigOperatorClicked);

    //! [4]

    //! [5]
    QGridLayout *mainLayout = new QGridLayout;
    //! [5] //! [6]
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(display, 0, 0, 1, 6);
    mainLayout->addWidget(backspaceButton, 1, 0, 1, 2);
    mainLayout->addWidget(clearButton, 1, 2, 1, 2);
    mainLayout->addWidget(clearAllButton, 1, 4, 1, 2);
    mainLayout->addWidget(toUSDButton, 6, 0, 1, 3);
    mainLayout->addWidget(toTWDButton, 6, 3, 1, 3);
    mainLayout->addWidget(sinButton, 7, 0, 1, 2);
    mainLayout->addWidget(cosButton, 7, 2, 1, 2);
    mainLayout->addWidget(tanButton, 7, 4, 1, 2);
    mainLayout->addWidget(logButton, 8, 0, 1, 3);
    mainLayout->addWidget(powerXYButton, 8, 3, 1, 3);
    mainLayout->addWidget(clearMemoryButton, 2, 0);
    mainLayout->addWidget(readMemoryButton, 3, 0);
    mainLayout->addWidget(setMemoryButton, 4, 0);
    mainLayout->addWidget(addToMemoryButton, 5, 0);
    mainLayout->addWidget(arcsinButton, 9, 0, 1, 2);
    mainLayout->addWidget(arccosButton, 9, 2, 1, 2);
    mainLayout->addWidget(arctanButton, 9, 4, 1, 2);


    for (int i = 1; i < NumDigitButtons; ++i) {
        int row = ((9 - i) / 3) + 2;
        int column = ((i - 1) % 3) + 1;
        mainLayout->addWidget(digitButtons[i], row, column);
    }

    mainLayout->addWidget(digitButtons[0], 5, 1);
    mainLayout->addWidget(pointButton, 5, 2);
    mainLayout->addWidget(changeSignButton, 5, 3);

    mainLayout->addWidget(divisionButton, 2, 4);
    mainLayout->addWidget(timesButton, 3, 4);
    mainLayout->addWidget(minusButton, 4, 4);
    mainLayout->addWidget(plusButton, 5, 4);

    mainLayout->addWidget(squareRootButton, 2, 5);
    mainLayout->addWidget(powerButton, 3, 5);
    mainLayout->addWidget(reciprocalButton, 4, 5);
    mainLayout->addWidget(equalButton, 5, 5);
    setLayout(mainLayout);

    setWindowTitle(tr("Calculator"));
}
//! [6]

//! [7]
void Calculator::digitClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    int digitValue = clickedButton->text().toInt();
    if (display->text() == "0" && digitValue == 0.0)
        return;

    if (waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }
    display->setText(display->text() + QString::number(digitValue));
}
//! [7]

//! [8]
void Calculator::unaryOperatorClicked()
//! [8] //! [9]
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    double result = 0.0;

    if (clickedOperator == tr("Sqrt")) {
        if (operand < 0.0) {
            abortOperation();
            return;
        }
        result = std::sqrt(operand);
    } else if (clickedOperator == tr("x\302\262")) {
        result = std::pow(operand, 2.0);
    } else if (clickedOperator == tr("1/x")) {
        if (operand == 0.0) {
            abortOperation();
            return;
        }
        result = 1.0 / operand;
    }
    display->setText(QString::number(result));
    waitingForOperand = true;
}
//! [9]

//! [10]
void Calculator::additiveOperatorClicked()
//! [10] //! [11]
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    if (!clickedButton)
        return;
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();

    //! [11] //! [12]
    if (!pendingMultiplicativeOperator.isEmpty()) {
        //! [12] //! [13]
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(factorSoFar));
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }

    //! [13] //! [14]
    if (!pendingAdditiveOperator.isEmpty()) {
        //! [14] //! [15]
        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(sumSoFar));
    } else {
        sumSoFar = operand;
    }

    //! [15] //! [16]
    pendingAdditiveOperator = clickedOperator;
    //! [16] //! [17]
    waitingForOperand = true;
}
//! [17]

//! [18]
void Calculator::multiplicativeOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    if (!clickedButton)
        return;
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(factorSoFar));
    } else {
        factorSoFar = operand;
    }

    pendingMultiplicativeOperator = clickedOperator;
    waitingForOperand = true;
}
//! [18]

//! [20]
void Calculator::equalClicked()
{
    if (waitingForExponent) {
        double exponent = display->text().toDouble();
        double result = std::pow(baseForExponent, exponent);
        display->setText(QString::number(result, 'g', 15));
        waitingForExponent = false;
        waitingForOperand = true;
        return;
    }

    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }
    if (!pendingAdditiveOperator.isEmpty()) {
        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }
        pendingAdditiveOperator.clear();
    } else {
        sumSoFar = operand;
    }

    display->setText(QString::number(sumSoFar));
    sumSoFar = 0.0;
    waitingForOperand = true;
}
//! [20]

//! [22]
void Calculator::pointClicked()
{
    if (waitingForOperand)
        display->setText("0");
    if (!display->text().contains('.'))
        display->setText(display->text() + tr("."));
    waitingForOperand = false;
}
//! [22]

//! [24]
void Calculator::changeSignClicked()
{
    QString text = display->text();
    double value = text.toDouble();

    if (value > 0.0) {
        text.prepend(tr("-"));
    } else if (value < 0.0) {
        text.remove(0, 1);
    }
    display->setText(text);
}
//! [24]

//! [26]
void Calculator::backspaceClicked()
{
    if (waitingForOperand)
        return;

    QString text = display->text();
    text.chop(1);
    if (text.isEmpty()) {
        text = "0";
        waitingForOperand = true;
    }
    display->setText(text);
}
//! [26]

//! [28]
void Calculator::clear()
{
    if (waitingForOperand)
        return;

    display->setText("0");
    waitingForOperand = true;
}
//! [28]

//! [30]
void Calculator::clearAll()
{
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    display->setText("0");
    waitingForOperand = true;
}
//! [30]

//! [32]
void Calculator::clearMemory()
{
    sumInMemory = 0.0;
}

void Calculator::readMemory()
{
    display->setText(QString::number(sumInMemory));
    waitingForOperand = true;
}

void Calculator::setMemory()
{
    equalClicked();
    sumInMemory = display->text().toDouble();
}

void Calculator::addToMemory()
{
    equalClicked();
    sumInMemory += display->text().toDouble();
}
//! [32]
//! [34]
template<typename PointerToMemberFunction>
Button *Calculator::createButton(const QString &text, const PointerToMemberFunction &member)
{
    Button *button = new Button(text);
    connect(button, &Button::clicked, this, member);
    return button;
}
//! [34]

//! [36]
void Calculator::abortOperation()
{
    clearAll();
    display->setText(tr("####"));
}
//! [36]

void Calculator::convertToUSD()
{
    double ntd = display->text().toDouble();
    double usd = ntd / 30.0;
    display->setText(QString::number(usd, 'f', 2));
    waitingForOperand = true;
}

void Calculator::convertToTWD()
{
    double usd = display->text().toDouble();
    double ntd = usd * 30.0;
    display->setText(QString::number(ntd, 'f', 2));
    waitingForOperand = true;
}

void Calculator::unaryTrigOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    double result = 0.0;

    // 將輸入視為角度，轉為弧度
    double radians = qDegreesToRadians(operand);

    if (clickedOperator == tr("sin")) {
        result = std::sin(radians);
    } else if (clickedOperator == tr("cos")) {
        result = std::cos(radians);
    } else if (clickedOperator == tr("tan")) {
        result = std::tan(radians);
    }

    display->setText(QString::number(result, 'g', 10));
    waitingForOperand = true;
}

void Calculator::unaryLogOperatorClicked()
{
    double operand = display->text().toDouble();
    double result = 0.0;

    if (operand <= 0.0) {
        abortOperation();  // log 無法對非正數取值
        return;
    }

    result = std::log10(operand);  // 以10為底的log
    display->setText(QString::number(result, 'g', 10));
    waitingForOperand = true;
}

void Calculator::powerXYClicked()
{
    baseForExponent = display->text().toDouble(); // 儲存 x
    waitingForExponent = true;
    waitingForOperand = true; // 準備讓使用者輸入 y
}


void Calculator::unaryARCTrigOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    if (!clickedButton) return; // 確保按鈕有效
    QString clickedOperator = clickedButton->text();

    // 從顯示器取得輸入數字
    bool ok;
    double x = display->text().toDouble(&ok);
    if (!ok || display->text().isEmpty()) {
        display->setText("錯誤：請輸入有效數字！");
        return;
    }

    // 檢查範圍（arcsin 和 arccos 需要 x 在 [-1, 1] 之間）
    if ((clickedOperator == tr("arcsin") || clickedOperator == tr("arccos")) && (x < -1 || x > 1)) {
        display->setText("錯誤：輸入必須在 -1 到 1 之間！");
        return;
    }

    double result = 0.0;

    // 計算反三角函數（結果以度數顯示）
    if (clickedOperator == tr("arcsin")) {
        double arcsin_rad = asin(x);
        result = arcsin_rad * 180 / M_PI; // 轉為度數
    } else if (clickedOperator == tr("arccos")) {
        double arccos_rad = acos(x);
        result = arccos_rad * 180 / M_PI; // 轉為度數
    } else if (clickedOperator == tr("arctan")) {
        double arctan_rad = atan(x);
        result = arctan_rad * 180 / M_PI; // 轉為度數
    } else {
        display->setText("錯誤：無效運算！");
        return;
    }

    // 顯示結果（小數點後 6 位）
    display->setText(QString::number(result, 'f', 6));
    waitingForOperand = true;
}


//! [38]
bool Calculator::calculate(double rightOperand, const QString &pendingOperator)
{
    if (pendingOperator == tr("+")) {
        sumSoFar += rightOperand;
    } else if (pendingOperator == tr("-")) {
        sumSoFar -= rightOperand;
    } else if (pendingOperator == tr("\303\227")) {
        factorSoFar *= rightOperand;
    } else if (pendingOperator == tr("\303\267")) {
        if (rightOperand == 0.0)
            return false;
        factorSoFar /= rightOperand;
    }
    return true;
}
//! [38]
