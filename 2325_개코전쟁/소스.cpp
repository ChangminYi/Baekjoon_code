#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <numeric>

using namespace std;

typedef pair<int, int> pint;

const int INF = INT32_MAX / 2;
const int NO_PARENT = -1;

int n, m;
vector<vector<pint>> graph;
vector<vector<bool>> usable;
vector<int> dist, parent;
priority_queue<pint, vector<pint>, greater<pint>> pq;

int dijk(int start, int dest, bool init_par) {
    fill(dist.begin(), dist.end(), INF);

    dist[start] = 0;
    pq.push(pint(0, start));
    while (!pq.empty()) {
        int cur = pq.top().second;
        int cur_dist = pq.top().first;
        pq.pop();

        if (cur_dist <= dist[cur]) {
            for (const pint& edge : graph[cur]) {
                int nxt = edge.first;
                int new_dist = cur_dist + edge.second;

                if (usable[cur][nxt] && new_dist < dist[nxt]) {
                    dist[nxt] = new_dist;
                    pq.push(pint(new_dist, nxt));

                    if (init_par) {
                        parent[nxt] = cur;
                    }
                }
            }
        }
    }

    return dist[dest];
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    graph.resize(n + 1);
    usable.resize(n + 1, vector<bool>(n + 1, true));
    dist.resize(n + 1);
    parent.resize(n + 1, NO_PARENT);

    for (int i = 0, n1, n2, w; i < m; i++) {
        cin >> n1 >> n2 >> w;
        graph[n1].push_back(pint(n2, w));
        graph[n2].push_back(pint(n1, w));
    }

    /*
    * 초기에 다익스트라 알고리즘을 한 번 실행하여 최단거리에서의
    * 특정 노드의 직전 노드 초기화. 그리고 n번 노드에서부터 직전 노드들을
    * 따라가면서, 직전 노드와 현재 노드 간 간선이 사용 불가능일 때의
    * 거리를 다익스트라로 계속 구하여 최댓값 갱신.
    * 노드가 최대 1000개이므로 시간초과는 나지 않음.
    */
    dijk(1, n, true);

    int max_dist = 0;
    for (int cur = n; parent[cur] != NO_PARENT; cur = parent[cur]) {
        usable[parent[cur]][cur] = false, usable[cur][parent[cur]] = false;
        max_dist = max(max_dist, dijk(1, n, false));
        usable[parent[cur]][cur] = true, usable[cur][parent[cur]] = true;
    }

    cout << max_dist;

    return 0;
}