#include "atom.h"

typedef std::shared_ptr<Atom> ptr;
const int N = 100;

map<string, int> str2id;
map<int, string> id2str;

int id[N][N], id_cnt, ans[N], tans[N], rows, cols;
bool meiju[N][N], ans_found;
ptr atom[N][N];

void dfs(int x, int y) {
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
            for (int i = 0; i < 10; ++i) {
                tans[p] = i;
                dfs(x, y);
            }
            return;
        }
        else
            atom[x][y]->set(tans[p]);
    }
    atom[x][y]->cal();
    if (p) {
        if (tans[p] == -1)
            tans[p] = atom[x][y]->getValue();
        else if (tans[p] != atom[x][y]->getValue())
            return;
    }
    dfs(x + 1, y);
}

void search() {
    ans_found = 0;
    for (int i = 1; i <= id_cnt; ++i)
        tans[i] = ans[i] = -1;
    dfs(0, 0);
}
