#include "solver.h"

Solver::Solver()
{

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

void Solver::initPlus(const vector<SolverData> &Meiju, const vector<SolverData> &Other, int n, int m) {
    initValue(n, m);
    for (auto i : Meiju)
        _initPlus(i, 1);
    for (auto i : Other)
        _initPlus(i, 0);
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

void Solver::test() {
    Solver s;
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

void Solver::_initPlus(const SolverData &i, bool mj) {
    int x = i.x, y = i.y;
    const string &str = i.data;
    if ('0' <= str[0] && str[0] <= '9')
        num[x][y] = str[0] - '0';
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

