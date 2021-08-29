#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_NODE = 100001;
const int MAX_DEPTH = 21;

int n;
vector<vector<int>> par(MAX_NODE, vector<int>(MAX_DEPTH));
vector<bool> visit(MAX_NODE);
vector<int> depth(MAX_NODE);
vector<vector<int>> tree(MAX_NODE);

void init_tree(int root, int cur_depth) {
    visit[root] = true;
    depth[root] = cur_depth;
    for (int& nxt : tree[root]) {
        if (!visit[nxt]) {
            par[nxt][0] = root;
            init_tree(nxt, cur_depth + 1);
        }
    }
}

void init_parent() {
    for (int j = 1; j < MAX_DEPTH; j++) {
        for (int i = 1; i <= n; i++) {
            par[i][j] = par[par[i][j - 1]][j - 1];
        }
    }
}

int get_LCA(int node1, int node2) {
    if (depth[node1] < depth[node2]) {
        swap(node1, node2);
    }

    for (int i = MAX_DEPTH - 1; i >= 0; i--) {
        int dep_diff = depth[node1] - depth[node2];
        if (dep_diff >= (1 << i)) {
            node1 = par[node1][i];
        }
    }

    if (node1 == node2) {
        return node1;
    }
    else {
        for (int i = MAX_DEPTH - 1; i >= 0; i--) {
            if (par[node1][i] != par[node2][i]) {
                node1 = par[node1][i];
                node2 = par[node2][i];
            }
        }
        return par[node1][0];
    }
}

int main() {
    cin.tie(nullptr);
    cin.sync_with_stdio(false);
    cout.tie(nullptr);
    cout.sync_with_stdio(false);

    cin >> n;
    for (int i = 0, frt, bck; i < n - 1; i++) {
        cin >> frt >> bck;

        tree[frt].push_back(bck);
        tree[bck].push_back(frt);
    }
    init_tree(1, 0);
    init_parent();

    int iter;
    cin >> iter;
    do {
        int node1, node2;
        cin >> node1 >> node2;
        cout << get_LCA(node1, node2) << '\n';
    } while (--iter > 0);

    return 0;
}