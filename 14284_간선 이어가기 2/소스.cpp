#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <numeric>

using namespace std;

typedef pair<int, int> pint;

const int INF = INT32_MAX / 2;

int n, m, s, t;
vector<vector<pint>> graph;
vector<int> dist;
priority_queue<pint, vector<pint>, greater<pint>> pq;

void dijk() {
    dist[s] = 0;

    pq.push(pint(0, s));
    while (!pq.empty()) {
        int cur = pq.top().second;
        int cur_dist = pq.top().first;
        pq.pop();

        if (cur_dist <= dist[cur]) {
            for (const pint& edge : graph[cur]) {
                int nxt = edge.first;
                int weight = edge.second;

                int new_dist = cur_dist + weight;
                int old_dist = dist[nxt];
                if (new_dist < old_dist) {
                    dist[nxt] = new_dist;
                    pq.push(pint(new_dist, nxt));
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    graph.resize(n + 1);
    dist.resize(n + 1, INF);
    for (int i = 0, n1, n2, w; i < m; i++) {
        cin >> n1 >> n2 >> w;
        graph[n1].push_back(pint(n2, w));
        graph[n2].push_back(pint(n1, w));
    }
    cin >> s >> t;

    /*
    * 간선을 잇는 것이라서 mst로 접근하는 것이 아니고,
    * 간선이 이어졌을 시의 최단거리를 보는 것이기 때문에
    * 다익스트라를 사용하여 해결.
    */
    dijk();

    cout << dist[t];

    return 0;
}