#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;
typedef pair<int, int> pint;

int n, r1, r2;
vector<vector<pint>> graph;
vector<int> dist, parent;
vector<bool> visit;

void bfs(const int start) {
    queue<int> que;

    parent[start] = start;
    dist[start] = 0;
    visit[start] = true;
    que.push(start);
    while (!que.empty()) {
        int cur = que.front();
        que.pop();

        for (const pint& edge : graph[cur]) {
            if (!visit[edge.first]) {
                visit[edge.first] = true;
                dist[edge.first] = dist[cur] + edge.second;
                parent[edge.first] = cur;
                que.push(edge.first);
            }
        }
    }
}

int get_max_weight() {
    int ret = 0;
    int cur = r2;
    while (parent[cur] != cur) {
        ret = max(ret, dist[cur] - dist[parent[cur]]);
        cur = parent[cur];
    }

    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> r1 >> r2;
    graph.resize(n + 1);
    dist.resize(n + 1);
    parent.resize(n + 1);
    visit.resize(n + 1, false);

    /*
    * 간선 정보를 이용해 어느 한 로봇의 위치로부터의 모든 노드로의
    * 최단거리를 구한다. 그와 동시에 parent를 이용해 역추적을 가능하게
    * 기록. 두 번째 로봇부터 첫 번째 로봇으로의 경로 중 가장 긴 길이를
    * 가지는 간선의 길이를 구하고, 전체 길이에서 그 값을 빼면 됨.
    */
    for (int i = 0, n1, n2, w; i < n - 1; i++) {
        cin >> n1 >> n2 >> w;
        graph[n1].push_back(pint(n2, w));
        graph[n2].push_back(pint(n1, w));
    }

    bfs(r1);

    cout << dist[r2] - get_max_weight();

    return 0;
}