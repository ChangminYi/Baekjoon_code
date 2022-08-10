#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct edge {
    int node, dist;
    edge(const int _n, const int _d) {
        node = _n, dist = _d;
    }
};

int n;
vector<edge> graph[50001];
int dist[3][50001];

int dfs(int idx, int cur) {
    int ret = cur;
    
    for(const edge& adj: graph[cur]) {
        if(dist[idx][adj.node] == INT32_MAX) {
            dist[idx][adj.node] = dist[idx][cur] + adj.dist;
            int tmp_ret = dfs(idx, adj.node);
            if(dist[idx][tmp_ret] > dist[idx][ret]) {
                ret = tmp_ret;
            }
        }
    }

    return ret;
}

int main() {
    /**
     * 트리에서의 최단 거리의 최댓값은 트리의 지름인 두 노드에서부터의
     * 거리 중 더 큰 값이다. 따라서, 지름을 구한 뒤 두 노드에서부터의
     * 전체 노드의 거리를 구하여 그 중 큰 값을 출력하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for(int i = 0, u, v, d; i < n - 1; i++) {
        cin >> u >> v >> d;
        graph[u].push_back(edge(v, d));
        graph[v].push_back(edge(u, d));
    }

    fill(dist[0] + 1, dist[0] + n + 1, INT32_MAX);
    fill(dist[1] + 1, dist[1] + n + 1, INT32_MAX);
    fill(dist[2] + 1, dist[2] + n + 1, INT32_MAX);
    dist[0][1] = 0;
    int p1 = dfs(0, 1);
    dist[1][p1] = 0;
    int p2 = dfs(1, p1);
    dist[2][p2] = 0;
    dfs(2, p2);

    for(int i = 1; i <= n; i++) {
        cout << max(dist[1][i], dist[2][i]) << '\n';
    }

    return 0;
}
