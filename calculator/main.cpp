#include <QApplication>
#include "calculator.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Calculator calc;
    calc.setWindowTitle("Qt Calculator");
    calc.resize(300, 400);
    calc.show();
    return app.exec();
}
