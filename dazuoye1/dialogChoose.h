#ifndef DIALOGCHOOSE_H
#define DIALOGCHOOSE_H

#include "header.h"

class PushButtonID : public QPushButton
{
    Q_OBJECT

public:
    explicit PushButtonID(int id, QWidget *parent = 0);

signals:
    void myClicked(int id);

private:
    int ID;

private slots:
    void slot_myClicked();
};


class DialogChoose : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChoose(const QList<QString> &list, QWidget *parent = 0);

    int getAnswer();

private:
    int answer;

    void setUI(const QList<QString> &list);
    void setConnection();

private slots:
    void myAccept(int id);

};

#endif // DIALOGCHOOSE_H
