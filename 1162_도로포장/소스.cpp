#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <cmath>
#include <numeric>

using namespace std;

typedef long long lli;
struct edge {
    int adj_node, dist;
    edge() : adj_node(0), dist(0) {}
    edge(const int _n, const int _d) : adj_node(_n), dist(_d) {}
};
struct pqn {
    int node, road_cnt;
    lli dist;
    pqn(const int _n, const int _r, const lli _d) : node(_n), road_cnt(_r), dist(_d) {}
    bool operator>(const pqn& other) const {
        return this->dist > other.dist;
    }
};

const lli INF = INT64_MAX / 2;

int n, m, k;
vector<edge> graph[10001];
lli dist[21][10001];
priority_queue<pqn, vector<pqn>, greater<pqn>> pq;

void dijk() {
    for (int i = 0; i <= k; i++) {
        fill(dist[i] + 1, dist[i] + n + 1, INF);
    }

    dist[0][1] = 0;
    pq.push(pqn(1, 0, 0));
    while (!pq.empty()) {
        int cur = pq.top().node;
        int cur_cnt = pq.top().road_cnt;
        lli cur_dist = pq.top().dist;
        pq.pop();

        if (cur_dist <= dist[cur_cnt][cur]) {
            for (const edge& e : graph[cur]) {
                int nxt = e.adj_node;
                lli new_dist = cur_dist + e.dist;

                if (new_dist < dist[cur_cnt][nxt]) {
                    dist[cur_cnt][nxt] = new_dist;
                    pq.push(pqn(nxt, cur_cnt, new_dist));
                }
                if (cur_cnt < k && cur_dist < dist[cur_cnt + 1][nxt]) {
                    dist[cur_cnt + 1][nxt] = cur_dist;
                    pq.push(pqn(nxt, cur_cnt + 1, cur_dist));
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * 다익스트라 알고리즘을 통해 최단거리를 구하지만,
    * dist 배열에 포장한 도로의 수가 추가된다. 따라서 2차원 배열.
    * 현재 노드에서 도로를 포장하지 않는 경우, 그리고 도로를 포장하는
    * 두 가지 경우에 대해서 최단거리를 갱신하면 된다.
    */
    cin >> n >> m >> k;
    for (int i = 0, n1, n2, w; i < m; i++) {
        cin >> n1 >> n2 >> w;
        graph[n1].push_back(edge(n2, w));
        graph[n2].push_back(edge(n1, w));
    }

    dijk();

    lli min_dist = INF;
    for (int i = 0; i <= k; i++) {
        min_dist = min(min_dist, dist[i][n]);
    }

    cout << min_dist;

    return 0;
}