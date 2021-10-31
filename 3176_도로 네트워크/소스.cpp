#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

typedef pair<int, int> pint;

const int MAX_COL = 21;
const int NOT_VISIT = -1;

int n, k;
vector<vector<pint>> graph;
vector<int> depth;
vector<vector<int>> parent, min_dist, max_dist;

/*
* 간선 정보만 주어졌기 때문에, dfs를 한번 실행하여
* 노드의 깊이 정보, 최단/최장거리, 부모노드 초기화
*/
void dfs(int cur) {
    for (const pint& edge : graph[cur]) {
        if (depth[edge.first] == NOT_VISIT) {
            parent[edge.first][0] = cur;
            min_dist[edge.first][0] = edge.second;
            max_dist[edge.first][0] = edge.second;
            depth[edge.first] = depth[cur] + 1;
            dfs(edge.first);
        }
    }
}

/*
* 2^i번째 부모를 구하고, 그 노드까지의 최단/최장거리 업데이트
*/
void init_table() {
    for (int j = 1; j < MAX_COL; j++) {
        for (int i = 1; i <= n; i++) {
            parent[i][j] = parent[parent[i][j - 1]][j - 1];
            min_dist[i][j] = min(min_dist[i][j - 1], min_dist[parent[i][j - 1]][j - 1]);
            max_dist[i][j] = max(max_dist[i][j - 1], max_dist[parent[i][j - 1]][j - 1]);
        }
    }
}

pint get_lca(int x, int y) {
    int ret_min = INT32_MAX, ret_max = INT32_MIN;

    // y가 더 깊은 노드가 되도록 고정
    if (depth[x] > depth[y]) {
        swap(x, y);
    }

    // y를 2의 제곱수만큼 점프
    for (int i = MAX_COL - 1; i >= 0; i--) {
        if (depth[y] - depth[x] >= (1 << i)) {
            ret_min = min(ret_min, min_dist[y][i]);
            ret_max = max(ret_max, max_dist[y][i]);
            y = parent[y][i];
        }
    }

    if (x != y) {
        // x, y 둘다 2^i만큼 점프. 최단/최장거리 업데이트
        for (int i = MAX_COL - 1; i >= 0; i--) {
            if (parent[x][i] != parent[y][i]) {
                ret_min = min({ ret_min, min_dist[x][i], min_dist[y][i] });
                ret_max = max({ ret_max, max_dist[x][i], max_dist[y][i] });
                x = parent[x][i];
                y = parent[y][i];
            }
        }

        ret_min = min({ ret_min, min_dist[x][0], min_dist[y][0] });
        ret_max = max({ ret_max, max_dist[x][0], max_dist[y][0] });
    }

    return pint(ret_min, ret_max);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;

    graph = vector<vector<pint>>(n + 1);
    depth.resize(n + 1, NOT_VISIT);
    min_dist = vector<vector<int>>(n + 1, vector<int>(MAX_COL));
    max_dist = vector<vector<int>>(n + 1, vector<int>(MAX_COL));
    parent = vector<vector<int>>(n + 1, vector<int>(MAX_COL));

    for (int i = 0, n1, n2, w; i < n - 1; i++) {
        cin >> n1 >> n2 >> w;
        graph[n1].push_back(pint(n2, w));
        graph[n2].push_back(pint(n1, w));
    }

    // 루트는 임의로 1로 설정.
    depth[1] = 0;
    dfs(1);
    init_table();

    cin >> k;
    for (int i = 0, n1, n2; i < k; i++) {
        cin >> n1 >> n2;
        pint ret = get_lca(n1, n2);

        cout << ret.first << ' ' << ret.second << '\n';
    }

    return 0;
}