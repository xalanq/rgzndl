#ifndef DIALOGPLUSMINUS_H
#define DIALOGPLUSMINUS_H

#include "dialogShared.h"

class DialogPlusMinus : public DialogShared
{
    Q_OBJECT

public:
    explicit DialogPlusMinus(Solver::Type type, QWidget *parent = nullptr);

signals:

public slots:
    void addBlock(int id);
    void solve();

private:
    QLabel *lbl_line;
    Solver::Type _type;

    void initValue();
    void initUI();
    void initConnection();
};

#endif // DIALOGPLUSMINUS_H
