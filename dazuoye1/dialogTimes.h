#ifndef DIALOGTIMES_H
#define DIALOGTIMES_H

#include "dialogShared.h"

class DialogTimes : public DialogShared
{
    Q_OBJECT

public:
    explicit DialogTimes(QWidget *parent = nullptr);

signals:

public slots:
    void addBlock(int id);
    void solve();

private:
    QLabel *lbl_line1, *lbl_line2;

    void initValue();
    void initUI();
    void initConnection();
};

#endif // DIALOGTIMES_H
