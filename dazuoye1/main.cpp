#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    // BlockEdit e;
    // e.setFixedSize(50, 50);
    // e.show();
    WidgetPlusMinus w(Solver::Minus);
    w.show();
    w.setFixedHeight(w.height());
    // Solver::test();

    return a.exec();
}
