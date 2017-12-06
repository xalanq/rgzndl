#ifndef DIALOGPLUSMINUS_H
#define DIALOGPLUSMINUS_H

#include "header.h"
#include "dialogChoose.h"
#include "blockEdit.h"
#include "solver.h"

class DialogPlusMinus : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPlusMinus(Solver::Type type, QWidget *parent = nullptr);

signals:

public slots:
    void addBlock(int id);
    void solve();
    void showAnswer(bool checked);

private:
    QLabel *lbl_line;
    QList<QLabel *> lbls;
    QList<PushButtonID *> btns;
    QList<QHBoxLayout *> layouts;
    QPushButton *btn_solve;
    QCheckBox *cbox_display;
    QTextEdit *edit_answer;
    vector<SolverData> Answer, Position;
    int max_block;
    Solver::Type _type;

    void initValue();
    void initUI();
    void initConnection();

    void initTheWidgetSize(QWidget *widget);
    void initTheLayout(QLayout *layout);
    void initTheButton(QPushButton *btn);

    void setValue(int x, int y, const QString &str);
    BlockEdit *newBlockEdit(int x, int y);


public:
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // DIALOGPLUSMINUS_H
