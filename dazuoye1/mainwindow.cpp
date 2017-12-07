#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initValue();
    initUI();
    initConnection();
    welcome();
}

MainWindow::~MainWindow()
{

}

void MainWindow::initValue()
{

}

void MainWindow::initUI()
{
    setWindowTitle(APP_NAME);

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
}

void MainWindow::initConnection()
{
    ;
}

void MainWindow::welcome()
{
    QList<QString> list;
    list.push_back(tr("Plus"));
    list.push_back(tr("Minus"));
    list.push_back(tr("Times"));
    list.push_back(tr("Divide"));
    list.push_back(tr("About"));
    DialogChoose d(list);
    d.setWindowTitle(APP_NAME);
    if (d.exec() == QDialog::Accepted) {
        int ans = d.getAnswer();
        if (ans == 0)
            workPlus();
        else if (ans == 1)
            workMinus();
        else if (ans == 2)
            workTimes();
        else if (ans == 3)
            workDivide();
        else if (ans == 4)
            actionAbout();
        welcome();
    }
    else
        exit(0);
}

void MainWindow::actionAbout()
{
    QMessageBox::about(this,
                       tr("About %1")
                       .arg(APP_NAME),
                       tr("<center><b> %1 %2 </b></center> \
                           <p>CopyRight &copy; 2017 by %3.</p> \
                           <p>Contact me: %4 </p> \
                           <p>Blog: <a href=\'http://%5\'>%6</a></p> \
                           <p>Project page: <a href=\'https://%7\'>%8</a></p>\
                           <p>Lisence: LGPL v3.0</p>")
                       .arg(APP_NAME.toHtmlEscaped())
                       .arg(APP_VERSION.toHtmlEscaped())
                       .arg(AUTHOR_NAME.toHtmlEscaped())
                       .arg(AUTHOR_EMAIL.toHtmlEscaped())
                       .arg(AUTHOR_WEBSITE.toHtmlEscaped())
                       .arg(AUTHOR_WEBSITE.toHtmlEscaped())
                       .arg(APP_PAGE.toHtmlEscaped())
                       .arg(APP_PAGE.toHtmlEscaped()));
}

void MainWindow::workPlus()
{
    DialogPlusMinus d(Solver::Plus);
    d.setWindowTitle(APP_NAME + " - Plus");
    d.exec();
}

void MainWindow::workMinus()
{
    DialogPlusMinus d(Solver::Minus);
    d.setWindowTitle(APP_NAME + " - Minus");
    d.exec();
}

void MainWindow::workTimes()
{
    DialogTimes d;
    d.setWindowTitle(APP_NAME + " - Times");
    d.exec();
}

void MainWindow::workDivide()
{
    DialogDivide d;
    d.setWindowTitle(APP_NAME + " - Divide");
    d.exec();
}

