#ifndef DIALOGDIVIDE_H
#define DIALOGDIVIDE_H

#include "dialogShared.h"

class DialogDivide : public DialogShared
{
    Q_OBJECT

public:
    explicit DialogDivide(QWidget *parent = nullptr);

signals:

public slots:
    void addBlock(int id);
    void solve();

private:
    void initValue();
    void initUI();
    void initConnection();
};

#endif // DIALOGDIVIDE_H
