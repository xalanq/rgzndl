#include "dialogPlusMinus.h"

DialogPlusMinus::DialogPlusMinus(Solver::Type type, QWidget *parent) : DialogShared(parent)
{
    _type = type;
    initValue();
    initUI();
    initConnection();
}

void DialogPlusMinus::addBlock(int id)
{
    layouts[id]->insertWidget(1, newBlockEdit(id, layouts[id]->count() - 1));
    if (layouts[id]->count() > max_block) {
        max_block = layouts[id]->count();
        setMinimumWidth(std::max(515, 515 + 59 * (max_block - 5)));
    }
}

void DialogPlusMinus::solve()
{
    if (cbox_display->isChecked())
        return;
    Solver solver(_type);
    vector<SolverData> Meiju, Other;
    for (int i = 0; i < 3; ++i) {
        int len = layouts[i]->count() - 1;
        for (int j = len; j; --j) {
            string str = ((BlockEdit *)(layouts[i]->itemAt(j)->widget()))->text().toStdString();
            if (str != "") {
                if (i < 2)
                    Meiju.push_back(SolverData(str, i, len - j));
                else
                    Other.push_back(SolverData(str, i, len - j));
            }
        }
    }
    solver.init(Meiju, Other, 3, max_block - 1);
    auto answer = solver.solve();
    QString text;
    for (auto i : answer)
        text += QString::fromStdString(i.data) + " : " + QString::number(i.x) + "\n";
    if (text == "")
        text = "No solution!";
    edit_answer->setText(text);
    Answer = answer;
    Position.clear();
    for (auto i : Meiju)
        Position.push_back(i);
    for (auto i : Other)
        Position.push_back(i);
}

void DialogPlusMinus::initValue()
{
    for (int i = 0; i < 3; ++i) {
        btns.append(new PushButtonID(i, this));
        layouts.append(new QHBoxLayout);
    }
    lbl_line = new QLabel(this);
    max_block = 2;
}

void DialogPlusMinus::initUI()
{
    for (int i = 0; i < 3; ++i) {
        initTheButton(btns[i]);
        initTheWidgetSize(btns[i]);
        btns[i]->setText(tr("Add"));
        layouts[i]->addStretch();
        layouts[i]->addWidget(newBlockEdit(i, 0));
    }
    lbl_sign->setText(QString("<p style='font-size:40px; font-weight:bold'>") + (_type == Solver::Plus ? "＋" : "－") + "</p>");
    lbl_line->setMaximumHeight(2);
    lbl_line->setStyleSheet("background-color: #c0c0c0");

    auto layout_left = new QVBoxLayout;
    auto layout_mid = new QVBoxLayout;
    auto layout_right = new QVBoxLayout;
    auto layout_up = new QHBoxLayout;
    auto layout_down = new QHBoxLayout;
    auto layout_edit = new QVBoxLayout;
    auto layout_display = new QVBoxLayout;
    auto layout = new QHBoxLayout;

    initTheLayout(layout_left);
    initTheLayout(layout_mid);
    initTheLayout(layout_right);
    initTheLayout(layout_up);
    initTheLayout(layout_down);

    layout_left->addWidget(newLabel());
    layout_left->addWidget(lbl_sign);

    layout_mid->addLayout(layouts[0]);
    layout_mid->addLayout(layouts[1]);

    layout_right->addWidget(btns[0]);
    layout_right->addWidget(btns[1]);

    layout_up->addLayout(layout_left);
    layout_up->addLayout(layout_mid);
    layout_up->addLayout(layout_right);

    layout_down->addWidget(newLabel());
    layout_down->addLayout(layouts[2]);
    layout_down->addWidget(btns[2]);

    layout_edit->addLayout(layout_up);
    layout_edit->addWidget(lbl_line);
    layout_edit->addLayout(layout_down);
    layout_edit->addWidget(btn_solve);

    layout_display->addWidget(cbox_display);
    layout_display->addWidget(edit_answer);

    layout->addLayout(layout_edit);
    layout->addSpacing(25);
    layout->addLayout(layout_display);

    setLayout(layout);

    setMinimumWidth(515);
}

void DialogPlusMinus::initConnection()
{
    for (auto i : btns)
        connect(i, SIGNAL(myClicked(int)),
                this, SLOT(addBlock(int)));
}
