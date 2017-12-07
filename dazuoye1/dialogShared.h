#ifndef DIALOGSHARED_H
#define DIALOGSHARED_H

#include "header.h"
#include "blockEdit.h"
#include "dialogChoose.h"
#include "solver.h"

class DialogShared : public QDialog
{
    Q_OBJECT

public:
    explicit DialogShared(QWidget *parent = nullptr);

signals:

public slots:
    virtual void solve();
    void showAnswer(bool checked);

private:
    void initValue();
    void initUI();
    void initConnection();

protected:
    QList<PushButtonID *> btns;
    QList<QHBoxLayout *> layouts;
    QLabel *lbl_sign;
    QPushButton *btn_solve;
    QCheckBox *cbox_display;
    QTextEdit *edit_answer;
    vector<SolverData> Answer, Position;
    int max_block;

    void initTheWidgetSize(QWidget *widget);
    void initTheLayout(QLayout *layout);
    void initTheButton(QPushButton *btn);
    void setValue(int x, int y, const QString &str);
    BlockEdit *newBlockEdit(int x, int y);
    QLabel *newLabel();
    virtual void nextPosition(int &x, int &y);
    virtual void previousPosition(int &x, int &y);

public:
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // DIALOGSHARED_H
