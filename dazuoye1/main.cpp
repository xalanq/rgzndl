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
    WidgetPlus w;
    w.show();
    w.setFixedHeight(w.height());

    return a.exec();
}
