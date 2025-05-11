#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

class Calculator : public QWidget {
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);

private slots:
    void onDigitClicked();
    void onOperatorClicked();
    void onClearClicked();
    void onEqualClicked();

private:
    QLineEdit *display;
    QString currentInput;
    QString operand1;
    QString operand2;
    QString currentOperator;
    bool waitingForOperand;

    void createButton(const QString &text, QGridLayout *layout, int row, int col);
};

#endif // CALCULATOR_H
