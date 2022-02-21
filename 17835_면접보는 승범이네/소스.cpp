#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

struct edge {
    int node, weight;
    edge(const int _n, const int _w) : node(_n), weight(_w) {}
};

struct pqn {
    int node;
    long long dist;
    pqn(const int _n, const long long _d) : node(_n), dist(_d) {}
    bool operator>(const pqn& other) const { return dist > other.dist; }
};

const long long INF = INT64_MAX / 2;

int n, m, k;
vector<edge> graph[100'001];
long long dist[100'001];
priority_queue<pqn, vector<pqn>, greater<>> pq;

void dijk() {
    fill(dist, dist + n + 1, INF);

    dist[0] = 0;
    pq.push(pqn(0, 0));
    while (!pq.empty()) {
        int cur = pq.top().node;
        long long cur_dist = pq.top().dist;
        pq.pop();

        if (cur_dist <= dist[cur]) {
            for (const edge& e : graph[cur]) {
                long long new_dist = cur_dist + e.weight;
                if (new_dist < dist[e.node]) {
                    dist[e.node] = new_dist;
                    pq.push(pqn(e.node, new_dist));
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 면접장 기준이기 때문에, 그래프의 간선 방향을 반대로 설정해야 한다.
    * 0번 노드를 더미 노드로 설정하여 모든 면접장을 연결하였다.
    * 따라서, 0번 노드에서 가장 먼 노드가 가장 먼 도시의 번호가 된다.
    */

    cin >> n >> m >> k;
    for (int u, v, c; m; m--) {
        cin >> u >> v >> c;
        graph[v].push_back(edge(u, c));
    }
    for (int u; k; k--) {
        cin >> u;
        graph[0].push_back(edge(u, 0));
    }

    dijk();
    
    int max_idx = 0;
    long long max_dist = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] > max_dist) {
            max_idx = i;
            max_dist = dist[i];
        }
    }

    cout << max_idx << '\n' << max_dist;

    return 0;
}