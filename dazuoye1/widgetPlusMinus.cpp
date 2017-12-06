#include "widgetPlusMinus.h"

WidgetPlusMinus::WidgetPlusMinus(Solver::Type type, QWidget *parent) : QWidget(parent)
{
    _type = type;
    initValue();
    initUI();
    initConnection();
}

void WidgetPlusMinus::addBlock(int id)
{
    layouts[id]->insertWidget(1, newBlockEdit(id, layouts[id]->count() - 1));
    if (layouts[id]->count() > max_block) {
        max_block = layouts[id]->count();
        setMinimumWidth(std::max(515, 515 + 59 * (max_block - 5)));
    }
}

void WidgetPlusMinus::solve()
{
    if (cbox_display->isChecked())
        return;
    using std::vector;
    Solver solver(_type);
    vector<SolverData> Meiju, Other;
    int max_len = 0;
    for (int i = 0; i < 3; ++i) {
        int len = layouts[i]->count();
        max_len = std::max(max_len, len);
        for (int j = len - 1; j; --j) {
            string str = ((BlockEdit *)(layouts[i]->itemAt(j)->widget()))->text().toStdString();
            if (str != "") {
                if (i < 2)
                    Meiju.push_back(SolverData(str, i, len - 1 - j));
                else
                    Other.push_back(SolverData(str, i, len - 1 - j));
            }
        }
    }
    solver.init(Meiju, Other, 3, max_len);
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

void WidgetPlusMinus::showAnswer(bool checked)
{
    if (checked) {
        if (Answer.size()) {
            map<string, int> str2ans;
            for (auto i : Answer)
                str2ans[i.data] = i.x;
            for (auto i : Position)
                setValue(i.x, i.y, QString::number(str2ans[i.data]));
        }
    }
    else {
        if (Position.size()) {
            for (auto i : Position)
                setValue(i.x, i.y, QString::fromStdString(i.data));
        }
    }
}

void WidgetPlusMinus::initValue()
{
    lbls.clear();
    btns.clear();
    layouts.clear();
    for (int i = 0; i < 3; ++i) {
        lbls.append(new QLabel(this));
        btns.append(new PushButtonID(i, this));
        layouts.append(new QHBoxLayout);
    }
    lbl_line = new QLabel(this);
    btn_solve = new QPushButton(this);
    cbox_display = new QCheckBox(this);
    edit_answer = new QTextEdit(this);
    max_block = 1;
}

void WidgetPlusMinus::initUI()
{
    for (int i = 0; i < 3; ++i) {
        initTheButton(btns[i]);
        initTheWidgetSize(btns[i]);
        btns[i]->setText(tr("Add"));
        initTheWidgetSize(lbls[i]);
        layouts[i]->addStretch();
        layouts[i]->addWidget(newBlockEdit(i, 0));
    }
    lbls[1]->setText(QString("<p style='font-size:50px; font-weight:bold'>") + (_type == Solver::Plus ? "+" : "-") + "</p>");
    lbl_line->setMaximumHeight(2);
    lbl_line->setStyleSheet("background-color: #c0c0c0");
    initTheButton(btn_solve);
    btn_solve->setText(tr("Solve!!"));
    btn_solve->setFixedHeight(50);
    cbox_display->setText("&Show");
    cbox_display->setFixedWidth(100);
    cbox_display->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    edit_answer->setReadOnly(true);
    edit_answer->setFixedWidth(100);
    edit_answer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    edit_answer->setStyleSheet(" \
        QTextEdit { \
            font-size: 20px; \
        } \
        QScrollBar:vertical { \
            width:15px; \
        }"
    );

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

    layout_left->addWidget(lbls[0]);
    layout_left->addWidget(lbls[1]);

    layout_mid->addLayout(layouts[0]);
    layout_mid->addLayout(layouts[1]);

    layout_right->addWidget(btns[0]);
    layout_right->addWidget(btns[1]);

    layout_up->addLayout(layout_left);
    layout_up->addLayout(layout_mid);
    layout_up->addLayout(layout_right);

    layout_down->addWidget(lbls[2]);
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
    setWindowFlags(windowFlags()& ~Qt::WindowMaximizeButtonHint);
}

void WidgetPlusMinus::initConnection()
{
    for (auto i : btns)
        connect(i, SIGNAL(myClicked(int)),
                this, SLOT(addBlock(int)));
    connect(btn_solve, SIGNAL(clicked(bool)),
            this, SLOT(solve()));
    connect(cbox_display, SIGNAL(clicked(bool)),
            this, SLOT(showAnswer(bool)));
}

void WidgetPlusMinus::initTheLayout(QLayout *layout)
{
    layout->setContentsMargins(0, 0, 0, 0);
}

void WidgetPlusMinus::initTheButton(QPushButton *btn)
{
    btn->setStyleSheet(" \
        QPushButton { \
            border: 1px solid #8f8f91; \
            border-radius: 10px; \
            background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, \
                                         stop: 0 #f6f7fa, stop: 1 #dadbde); \
        } \
        QPushButton:pressed { \
            background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, \
                                         stop: 0 #dadbde, stop: 1 #f6f7fa); \
        } \
        QPushButton:flat { \
            border: none;  */ \
        } \
        QPushButton:default { \
            border-color: navy; \
        }"
                       );
}

void WidgetPlusMinus::setValue(int x, int y, const QString &str)
{
    int len = layouts[x]->count();
    auto block = (BlockEdit *)(layouts[x]->itemAt(len - 1 - y)->widget());
    block->setText(str);
}

BlockEdit *WidgetPlusMinus::newBlockEdit(int x, int y)
{
    BlockEdit *ret = new BlockEdit(x, y, this);
    ret->installEventFilter(this);
    return ret;
}

bool WidgetPlusMinus::eventFilter(QObject *watched, QEvent *event)
{
    if (event && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent) {
            if (keyEvent->key() == Qt::Key_Tab || keyEvent->key() == Qt::Key_Backtab) {
                auto widget = dynamic_cast<BlockEdit *> (focusWidget());
                if (widget) {
                    int x = widget->X(), y = layouts[x]->count() - 1 - widget->Y();
                    if (keyEvent->key() == Qt::Key_Backtab) {
                        if (y == 1) {
                            x = (x + 3 - 1) % 3;
                            y = layouts[x]->count() - 1;
                        }
                        else
                            y--;
                    }
                    else {
                        if (y == layouts[x]->count() - 1) {
                            x = (x + 1) % 3;
                            y = 1;
                        }
                        else
                            y++;
                    }
                    layouts[x]->itemAt(y)->widget()->setFocus();
                    return true;
                }
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void WidgetPlusMinus::initTheWidgetSize(QWidget *widget)
{
    widget->setFixedSize(QSize(50, 50));
    widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}
