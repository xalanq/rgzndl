#ifndef SOLVER_H
#define SOLVER_H

#include "atom.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>

using std::vector;
using std::map;
using std::string;

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

private:
    typedef std::shared_ptr<Atom> ptr;
    static const int N = 100;
    map<string, int> str2id;
    map<int, string> id2str;
    int id[N][N], num[N][N], id_cnt, ans[N], tans[N], rows, cols;
    bool meiju[N][N], used[10], ans_found;
    ptr atom[N][N];

public:
    Solver();
    vector<SolverData> solve();
     void initPlus(const vector<SolverData> &Meiju, const vector<SolverData> &Other, int n, int m);
     static void test();

private:
     void dfs(int x, int y);
     void initValue(int n, int m);
     void _initPlus(const SolverData &i, bool mj);
};

#endif // SOLVER_H
