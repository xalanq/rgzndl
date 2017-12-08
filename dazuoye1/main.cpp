#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/img/icon.jpg"));
    MainWindow w;
    w.show();

    return a.exec();
}
