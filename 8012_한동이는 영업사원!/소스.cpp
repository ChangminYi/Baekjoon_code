#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

const int MAX = 30001;
const int MAX_COL = 17;
const int ROOT = 1;

int n, m;
vector<vector<int>> graph, parent;
vector<int> depth, to_go;
bitset<MAX> visit;

void dfs(int cur) {
    for (const int& nxt : graph[cur]) {
        if (!visit[nxt]) {
            visit[nxt] = true;
            depth[nxt] = depth[cur] + 1;
            parent[nxt][0] = cur;
            dfs(nxt);
        }
    }
}

void init_parent() {
    for (int j = 1; j < MAX_COL; j++) {
        for (int i = 1; i <= n; i++) {
            parent[i][j] = parent[parent[i][j - 1]][j - 1];
        }
    }
}

int get_lca(int x, int y) {
    if (depth[x] > depth[y]) {
        swap(x, y);
    }

    for (int i = MAX_COL - 1; i >= 0; i--) {
        if (depth[y] - depth[x] >= (1 << i)) {
            y = parent[y][i];
        }
    }

    if (x != y) {
        for (int i = MAX_COL - 1; i >= 0; i--) {
            if (parent[x][i] != parent[y][i]) {
                x = parent[x][i];
                y = parent[y][i];
            }
        }

        y = parent[y][0];
    }

    return y;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    graph.resize(n + 1);
    parent.resize(n + 1, vector<int>(MAX_COL, ROOT));
    depth.resize(n + 1);
    visit.reset();

    for (int i = 0, n1, n2; i < n - 1; i++) {
        cin >> n1 >> n2;
        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
    }

    visit[1] = true;
    depth[1] = 0;
    dfs(1);
    init_parent();

    cin >> m;
    to_go.resize(m);
    for (int& i : to_go) {
        cin >> i;
    }

    /*
    * 인접한 도시로 이동하는 시간은 언제나 1.
    * 따라서, 거리를 노드의 깊이로 간주하여도 무방함.
    * 트리에서 최단경로는 depth[n1] + depth[n2] - 2 * depth[lca(n1, n2)]
    * 노드 간 최단경로 모두 합쳐 출력하면 됨.
    */
    long long sum = 0;
    for (int i = 1; i < m; i++) {
        int lca = get_lca(to_go[i - 1], to_go[i]);
        sum += ((long long)depth[to_go[i - 1]] + depth[to_go[i]]) - (2LL * depth[lca]);
    }

    cout << sum;

    return 0;
}