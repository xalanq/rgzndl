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
    QVBoxLayout *layout_left, *layout_middle, *layout_right;

    void initValue();
    void initUI();
    void initConnection();

protected:
    virtual void previousPosition(int &x, int &y);
    virtual void nextPosition(int &x, int &y);
};

#endif // DIALOGTIMES_H
