#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <cmath>

using namespace std;

struct edge {
    int node = 0, weight = 0, cost = 0;
    edge(int _n, int _w, int _c) : node(_n), weight(_w), cost(_c) {}
};

struct pqn {
    int node = 0, cost = 0, dist = 0;
    pqn(int _n, int _c, int _d) : node(_n), cost(_c), dist(_d) {}
    bool operator>(const pqn& other) { return dist > other.dist; }
};

const int INF = INT32_MAX / 2;

int k, n, r;
int dist[10'001][101];
vector<edge> graph[101];
priority_queue<pqn, vector<pqn>, greater<>> pq;

void dijk() {
    for (int i = 0; i <= k; i++) fill(dist[i] + 1, dist[i] + n + 1, INF);

    dist[0][1] = 0;
    pq.push(pqn(1, 0, 0));
    while (!pq.empty()) {
        int cur = pq.top().node;
        int cur_dist = pq.top().dist;
        int cur_cost = pq.top().cost;
        pq.pop();

        if (cur_dist <= dist[cur_cost][cur]) {
            for (const edge& e : graph[cur]) {
                int new_cost = cur_cost + e.cost;
                int new_dist = cur_dist + e.weight;
                if (new_cost <= k && new_dist < dist[new_cost][e.node]) {
                    dist[new_cost][e.node] = new_dist;
                    pq.push(pqn(e.node, new_cost, new_dist));
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 제한이 걸린 최단거리 찾기. 다익스트라 알고리즘을 사용하는 것은 맞지만,
    * 거리를 저장할 때, 특정 비용을 사용하여 특정 노드로 가는 최단거리로
    * 모델링을 해야 한다. 따라서 dist 배열은 2차원이 된다.
    * 그리고 k원 이하의 모든 비용에서 최단거리를 찾으면 된다.
    */

    cin >> k >> n >> r;
    for (int s, d, l, t; r; r--) {
        cin >> s >> d >> l >> t;
        graph[s].push_back(edge(d, l, t));
    }

    dijk();

    int min_dist = INF;
    for (int i = 0; i <= k; i++) {
        min_dist = min(min_dist, dist[i][n]);
    }

    cout << (min_dist == INF ? -1 : min_dist);

    return 0;
}