#include "dialogTimes.h"

DialogTimes::DialogTimes(QWidget *parent) : DialogShared(parent)
{
    initValue();
    initUI();
    initConnection();
}

void DialogTimes::addBlock(int id)
{
    int cnt1 = layouts[0]->count() - 1, cnt2 = layouts[1]->count() - 1, tot = 0;
    if (id == 0) {
        layouts[0]->insertWidget(1, newBlockEdit(0, cnt1++));
        for (int i = 0; i < cnt2; ++i)
            layouts[3 + i]->insertWidget(1, newBlockEdit(3 + i, cnt1 + i));
        tot = cnt1 + cnt2 + 1;
        layouts[2]->insertWidget(1, newBlockEdit(2, layouts[2]->count() - 1));
    }
    else if (id == 1) {
        layouts[1]->insertWidget(1, newBlockEdit(1, cnt2));
        auto layout = new QHBoxLayout;
        layouts.append(layout);
        layout->addStretch();
        for (int i = 0; i < cnt2; ++i)
            layout->addWidget(newLabel());
        for (int i = 0; i <= cnt1; ++i)
            layout->insertWidget(1, newBlockEdit(3 + cnt2, cnt2 + i));
        layout_left->addWidget(newLabel());
        layout_middle->addLayout(layout);
        layout_right->addWidget(newLabel());
        ++cnt2;
        tot = cnt1 + cnt2 + 1;
        layouts[2]->insertWidget(1, newBlockEdit(2, layouts[2]->count() - 1));
    }
    if (tot > max_block) {
        max_block = tot;
        setMinimumWidth(std::max(515, 515 + 59 * (max_block - 5)));
    }
}

void DialogTimes::solve()
{
    if (cbox_display->isChecked())
        return;
    Solver solver(Solver::Times);
    vector<SolverData> Meiju, Other;
    Position.clear();
    for (int i = 0; i < layouts.size(); ++i)
        for (int j = 0; j < layouts[i]->count(); ++j) {
            auto widget = dynamic_cast<BlockEdit *> (layouts[i]->itemAt(j)->widget());
            if (widget) {
                string str = widget->text().toStdString();
                if (str != "") {
                    int x = widget->X(), y = widget->Y();
                    if (x == 2)
                        x = layouts.size() - 1;
                    else if (x > 2)
                        x--;
                    if (x < 2)
                        Meiju.push_back(SolverData(str, x, y));
                    else
                        Other.push_back(SolverData(str, x, y));
                    Position.push_back(SolverData(str, widget->X(), widget->Y()));
                }
            }
        }
    solver.init(Meiju, Other, layouts.size(), max_block - 1);
    auto answer = solver.solve();
    QString text;
    for (auto i : answer)
        text += QString::fromStdString(i.data) + " : " + QString::number(i.x) + "\n";
    if (text == "")
        text = "No solution!";
    edit_answer->setText(text);
    Answer = answer;
}

void DialogTimes::initValue()
{
    for (int i = 0; i < 4; ++i)
        layouts.append(new QHBoxLayout);
    for (int i = 0; i < 2; ++i)
        btns.append(new PushButtonID(i, this));
    lbl_line1 = new QLabel(this);
    lbl_line2 = new QLabel(this);
    max_block = 3;
}

void DialogTimes::initUI()
{
    for (int i = 0; i < 2; ++i) {
        initTheButton(btns[i]);
        initTheWidgetSize(btns[i]);
        btns[i]->setText(tr("Add"));
    }
    for (int i = 0; i < 4; ++i) {
        layouts[i]->addStretch();
        layouts[i]->addWidget(newBlockEdit(i, 0));
        if (i >= 2)
            layouts[i]->insertWidget(1, newBlockEdit(i, 1));
    }
    lbl_sign->setText(QString("<p style='font-size:40px; font-weight:bold'>") + "×" + "</p>");
    lbl_line1->setMaximumHeight(2);
    lbl_line1->setStyleSheet("background-color: #c0c0c0");
    lbl_line2->setMaximumHeight(2);
    lbl_line2->setStyleSheet("background-color: #c0c0c0");

    layout_left = new QVBoxLayout;
    layout_middle = new QVBoxLayout;
    layout_right = new QVBoxLayout;
    auto layout_up = new QHBoxLayout;
    auto layout_mid = new QHBoxLayout;
    auto layout_down = new QHBoxLayout;
    auto layout_edit = new QVBoxLayout;
    auto layout_display = new QVBoxLayout;
    auto layout = new QHBoxLayout;

    initTheLayout(layout_left);
    initTheLayout(layout_middle);
    initTheLayout(layout_right);
    initTheLayout(layout_up);
    initTheLayout(layout_mid);
    initTheLayout(layout_down);

    layout_left->addWidget(newLabel());
    layout_left->addWidget(lbl_sign);

    layout_middle->addLayout(layouts[0]);
    layout_middle->addLayout(layouts[1]);

    layout_right->addWidget(btns[0]);
    layout_right->addWidget(btns[1]);

    layout_up->addLayout(layout_left);
    layout_up->addLayout(layout_middle);
    layout_up->addLayout(layout_right);

    layout_left = new QVBoxLayout;
    layout_middle = new QVBoxLayout;
    layout_right = new QVBoxLayout;
    initTheLayout(layout_left);
    initTheLayout(layout_middle);
    initTheLayout(layout_right);
    layout_left->addWidget(newLabel());
    layout_middle->addLayout(layouts[3]);
    layout_right->addWidget(newLabel());
    layout_mid->addLayout(layout_left);
    layout_mid->addLayout(layout_middle);
    layout_mid->addLayout(layout_right);

    layout_down->addWidget(newLabel());
    layout_down->addLayout(layouts[2]);
    layout_down->addWidget(newLabel());

    layout_edit->addLayout(layout_up);
    layout_edit->addWidget(lbl_line1);
    layout_edit->addLayout(layout_mid);
    layout_edit->addWidget(lbl_line2);
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

void DialogTimes::initConnection()
{
    for (auto i : btns)
        connect(i, SIGNAL(myClicked(int)),
                this, SLOT(addBlock(int)));
}

void DialogTimes::previousPosition(int &x, int &y)
{
    if (y == 1) {
        if (x == 0)
            x = 2;
        else if (x == 2)
            x = layouts.size() - 1;
        else if (x == 3)
            x = 1;
        else
            x = x - 1;
        y = layouts[x]->count() - 1;
    }
    else
        y--;
}

void DialogTimes::nextPosition(int &x, int &y)
{
    if (y == layouts[x]->count() - 1) {
        if (x == 1)
            x = 3;
        else if (x == 2)
            x = 0;
        else if (x == layouts.size() - 1)
            x = 2;
        else
            x = x + 1;
        y = 1;
    }
    else
        y++;
}
