#include "solver.h"

Solver::Solver(Type type)
{
    _type = type;
}

vector<SolverData> Solver::solve() {
    ans_found = 0;
    for (int i = 0; i < 10; ++i)
        used[i] = 0;
    for (int i = 1; i <= id_cnt; ++i)
        tans[i] = ans[i] = -1;
    dfs(0, 0);
    vector<SolverData> ret;
    if (ans_found)
        for (int i = 1; i <= id_cnt; ++i)
            ret.push_back(SolverData(id2str[i], ans[i], -1));
    std::sort(ret.begin(), ret.end());
    return ret;
}

void Solver::init(const vector<SolverData> &Meiju, const vector<SolverData> &Other, int n, int m)
{
    if (_type == Plus)
        initPlus(Meiju, Other, n, m);
    else if (_type == Minus)
        initMinus(Meiju, Other, n, m);
    else if (_type == Times)
        initTimes(Meiju, Other, n, m);
    else if (_type == Divide)
        initDivide(Meiju, Other, n, m);
}

void Solver::test() {
    Solver s(Plus);
    vector<SolverData> Meiju, Other;
    Meiju.push_back(SolverData("A", 0, 0));
    Meiju.push_back(SolverData("B", 0, 1));
    Meiju.push_back(SolverData("A", 1, 1));
    Meiju.push_back(SolverData("B", 1, 0));
    Other.push_back(SolverData("C", 2, 0));
    Other.push_back(SolverData("C", 2, 1));
    s.initPlus(Meiju, Other, 3, 2);
    vector<SolverData> answer = s.solve();
    for (auto i : answer) {
        std::cout << i.data << " : " << i.x << std::endl;
    }
}

void Solver::dfs(int x, int y) {
    if (ans_found == 1)
        return;
    if (x >= rows) {
        dfs(0, y + 1);
        return;
    }
    if (y >= cols) {
        for (int i = 1; i <= id_cnt; ++i)
            ans[i] = tans[i];
        ans_found = 1;
        return;
    }
    int p = id[x][y];
    if (meiju[x][y]) {
        if (tans[p] == -1) {
            for (int i = 0; i < 10; ++i)
                if (!used[i]) {
                    tans[p] = i;
                    used[i] = 1;
                    dfs(x, y);
                    used[i] = 0;
                    tans[p] = -1;
                }
            return;
        }
        else
            atom[x][y]->set(tans[p]);
    }
    atom[x][y]->cal(true);
    int val = atom[x][y]->get() % 10;
    bool back = 0;
    if (p) {
        if (tans[p] == -1) {
            if (used[val])
                return;
            used[val] = 1;
            tans[p] = val;
            back = 1;
        }
        else if (tans[p] != val)
            return;
    }
    else {
        if (num[x][y] != val)
            return;
    }
    dfs(x + 1, y);
    if (p && back) {
        tans[p] = -1;
        used[val] = 0;
    }
}

void Solver::initValue(int n, int m) {
    id2str.clear();
    str2id.clear();
    id_cnt = 0;
    rows = n;
    cols = m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            id[i][j] = 0;
            num[i][j] = 0;
            meiju[i][j] = 0;
            atom[i][j] = Atom::fromInt(0);
        }
}

void Solver::_init(const SolverData &i, bool mj) {
    int x = i.x, y = i.y;
    const string &str = i.data;
    if ('0' <= str[0] && str[0] <= '9') {
        num[x][y] = str[0] - '0';
        if (mj)
            atom[x][y]->set(num[x][y]);
    }
    else {
        int &t = str2id[str];
        if (!t) {
            t = ++id_cnt;
            id2str[t] = str;
        }
        id[x][y] = t;
        meiju[x][y] = mj;
    }
}

void Solver::initPlus(const vector<SolverData> &Meiju, const vector<SolverData> &Other, int n, int m) {
    initValue(n, m);
    for (auto i : Meiju)
        _init(i, 1);
    for (auto i : Other)
        _init(i, 0);
    ptr TEN = Atom::fromInt(10);
    for (int i = 0; i < m; ++i) {
        atom[2][i] = atom[0][i] + atom[1][i];
        if (i)
            atom[2][i] = atom[2][i] + atom[2][i - 1] / TEN;
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            atom[i][j]->setDone(1);
}

void Solver::initMinus(const vector<SolverData> &Meiju, const vector<SolverData> &Other, int n, int m)
{
    initValue(n, m);
    for (auto i : Meiju)
        if (i.x == 1)
            _init(i, 1);
        else if (i.x == 0)
            _init(SolverData(i.data, 2, i.y), 0);
    for (auto i : Other)
        _init(SolverData(i.data, 0, i.y), 1);
    ptr TEN = Atom::fromInt(10);
    for (int i = 0; i < m; ++i) {
        atom[2][i] = atom[0][i] + atom[1][i];
        if (i)
            atom[2][i] = atom[2][i] + atom[2][i - 1] / TEN;
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            atom[i][j]->setDone(1);
}

void Solver::initTimes(const vector<SolverData> &Meiju, const vector<SolverData> &Other, int n, int m)
{
    int cnt[2] = {0, 0};
    for (auto i : Meiju)
        ++cnt[i.x];
    m = std::max(m, cnt[0] + cnt[1]);
    initValue(n, m);
    for (auto i : Meiju)
        _init(i, 1);
    for (auto i : Other)
        _init(i, 0);
    ptr TEN = Atom::fromInt(10);
    for (int i = 0; i < cnt[0]; ++i)
        for (int j = 0; j < cnt[1]; ++j)
            atom[2 + j][i + j] = atom[2 + j][i + j] + atom[0][i] * atom[1][j];
    for (int i = 0; i < cnt[1]; ++i)
        for (int j = 1; j <= cnt[0]; ++j)
            atom[i + 2][i + j] = atom[i + 2][i + j] + atom[i + 2][i + j - 1] / TEN;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < cnt[1]; ++j)
            atom[n - 1][i] = atom[n - 1][i] + atom[2 + j][i];
        if (i)
            atom[n - 1][i] = atom[n - 1][i] + atom[n - 1][i - 1] / TEN;
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            atom[i][j]->setDone(1);
}

void Solver::initDivide(const vector<SolverData> &Meiju, const vector<SolverData> &Other, int n, int m)
{
    initValue(n, m);
    for (auto i : Meiju)
        _init(i, 1);
    for (auto i : Other)
        _init(i, 0);
    ptr TEN = Atom::fromInt(10);
    for (int i = 0; i < m; ++i) {
        atom[2][i] = atom[0][i] + atom[1][i];
        if (i)
            atom[2][i] = atom[2][i] + atom[2][i - 1] / TEN;
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            atom[i][j]->setDone(1);
}
