#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct edge {
    int node, time, cost;
    edge(const int _n = 0, const int _t = 0, const int _c = 0) : node(_n), time(_t), cost(_c) {}
};

struct pqn {
    int node, dist, cost;
    pqn(const int _n, const int _d, const int _c) : node(_n), dist(_d), cost(_c) {}
    bool operator>(const pqn& other) {
        if (this->dist == other.dist) return this->cost > other.cost;
        else return this->dist > other.dist;
    }
};

const int INF = INT32_MAX / 2;

int n, t, m, l;
vector<edge> graph[101];
int dist[10001][101];
priority_queue<pqn, vector<pqn>, greater<>> pq;

int main() {
    /*
    * 다익스트라 알고리즘으로 최단거리 탐색.
    * 단, 총 소요 비용이 제한 조건에 추가되어 있으므로,
    * 각 가격에 대하여 최단거리를 구함. 따라서 dist 배열이 2차원.
    */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> t >> m >> l;
    for (int n1, n2, time, cost; l > 0; l--) {
        cin >> n1 >> n2 >> time >> cost;
        graph[n1].push_back(edge(n2, time, cost));
        graph[n2].push_back(edge(n1, time, cost));
    }

    for (int i = 0; i <= m; i++) {
        fill(dist[i] + 1, dist[i] + n + 1, INF);
    }
    dist[0][1] = 0;
    pq.push(pqn(1, 0, 0));
    while (!pq.empty()) {
        int cur = pq.top().node;
        int cur_dist = pq.top().dist;
        int cur_cost = pq.top().cost;
        pq.pop();

        if (cur_dist <= dist[cur_cost][cur]) {
            for (const edge& e : graph[cur]) {
                int nxt = e.node;
                int new_dist = cur_dist + e.time;
                int new_cost = cur_cost + e.cost;

                if (new_cost <= m && new_dist < dist[new_cost][nxt]) {
                    dist[new_cost][nxt] = new_dist;
                    pq.push(pqn(nxt, new_dist, new_cost));
                }
            }
        }
    }

    int min_cost = INF;
    for (int i = 0; i <= m; i++) {
        if (dist[i][n] <= t && i < min_cost) {
            min_cost = i;
        }
    }

    cout << (min_cost == INF ? -1 : min_cost);

    return 0;
}