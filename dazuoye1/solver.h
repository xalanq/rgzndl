#ifndef SOLVER_H
#define SOLVER_H

#include "atom.h"
#include "header.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

struct SolverData {
    string data;
    int x, y;
    SolverData(const string &data, int x, int y) : data(data), x(x), y(y) {}
    bool operator < (const SolverData &a) const {
        return data == a.data ? (x == a.x ? y < a.y : x < a.x) : data < a.data;
    }
};

class Solver
{

public:
    enum Type {Plus, Minus, Times, Divide};

    Solver(Type type);
    void init(const vector<SolverData> &Meiju, const vector<SolverData> &Other, int n, int m);
    vector<SolverData> solve();
    static void test();

private:
    typedef std::shared_ptr<Atom> ptr;
    static const int N = 100;
    map<string, int> str2id;
    map<int, string> id2str;
    int id[N][N], num[N][N], id_cnt, ans[N], tans[N], rows, cols;
    bool meiju[N][N], used[10], ans_found;
    ptr atom[N][N];
    Type _type;

    void dfs(int x, int y);
    void initValue(int n, int m);
    void _init(const SolverData &i, bool mj);
    void initPlus(const vector<SolverData> &Meiju, const vector<SolverData> &Other, int n, int m);
    void initMinus(const vector<SolverData> &Meiju, const vector<SolverData> &Other, int n, int m);
    void initTimes(const vector<SolverData> &Meiju, const vector<SolverData> &Other, int n, int m);
    void initDivide(const vector<SolverData> &Meiju, const vector<SolverData> &Other, int n, int m);
};

#endif // SOLVER_H
