#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <cmath>

using namespace std;

struct edge {
    int node, time, cost;
    edge(const int _n = 0, const int _t = 0, const int _c = 0) : node(_n), time(_t), cost(_c) {}
};

struct pqn {
    int node, dist, cost;
    pqn(const int _n = 0, const int _d = 0, const int _c = 0) : node(_n), dist(_d), cost(_c) {}
    bool operator>(const pqn& other) {
        if (dist != other.dist) return dist > other.dist;
        else return cost > other.cost;
    }
};

const int INF = INT32_MAX / 2;

int n, m, s, e, max_cost, ans;
vector<edge> graph[101];
bool visit[101];
int dist[10'001][101];
priority_queue<pqn, vector<pqn>, greater<>> pq;

void dijk() {
    for (int i = 0; i <= max_cost; i++) fill(dist[i] + 1, dist[i] + n + 1, INF);

    dist[0][s] = 0;
    pq.push(pqn(s, 0, 0));
    while (!pq.empty()) {
        int cur = pq.top().node;
        int cur_dist = pq.top().dist;
        int cur_cost = pq.top().cost;
        pq.pop();

        if (cur_dist <= dist[cur_cost][cur]) {
            for (const edge& e : graph[cur]) {
                int nxt_cost = cur_cost + e.cost;
                int nxt_dist = cur_dist + e.time;
                if (nxt_cost <= max_cost && nxt_dist < dist[nxt_cost][e.node]) {
                    dist[nxt_cost][e.node] = nxt_dist;
                    pq.push(pqn(e.node, nxt_dist, nxt_cost));
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 시간과 비용으로 다익스트라 알고리즘을 실행한다.
    * 최대로 사용하는 비용은 노드의 수 * 간선의 최대 비용이다.
    * 비용이 늘어날수록 거리는 줄어들어야 한다.
    */

    cin >> n >> m >> s >> e;
    for (int p, r, c, t; m; m--) {
        cin >> p >> r >> c >> t;
        graph[p].push_back(edge(r, t, c));
        graph[r].push_back(edge(p, t, c));
        max_cost = max(n * c, max_cost);
    }

    dijk();

    for (int i = 0, min_dist = max_cost; i <= max_cost; i++) {
        if (dist[i][e] != INF && dist[i][e] < min_dist) {
            ans++;
            min_dist = dist[i][e];
        }
    }

    cout << ans;

    return 0;
}