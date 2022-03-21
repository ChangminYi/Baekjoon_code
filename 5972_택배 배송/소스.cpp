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
    int node, dist;
    pqn(const int _n, const int _d) : node(_n), dist(_d) {}
    bool operator>(const pqn& other) { return dist > other.dist; }
};

const int INF = INT32_MAX / 2;

int n, m;
int dist[50'001];
vector<edge> graph[50'001];
priority_queue<pqn, vector<pqn>, greater<>> pq;

void dijk() {
    int nxt, new_dist;
    fill(dist + 1, dist + n + 1, INF);

    dist[1] = 0;
    pq.push(pqn(1, dist[1]));
    while (!pq.empty()) {
        int cur = pq.top().node;
        int cur_dist = pq.top().dist;
        pq.pop();

        if (cur_dist <= dist[cur]) {
            for (const edge& e : graph[cur]) {
                nxt = e.node;
                new_dist = cur_dist + e.weight;
                if (new_dist < dist[nxt]) {
                    dist[nxt] = new_dist;
                    pq.push(pqn(nxt, dist[nxt]));
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 간선의 가중치를 소에게 줘야 하는 여물로 설정.
    * 다익스트라 알고리즘으로 최단거리를 구하면 된다.
    */

    cin >> n >> m;
    for (int a, b, c; m; m--) {
        cin >> a >> b >> c;
        graph[a].push_back(edge(b, c));
        graph[b].push_back(edge(a, c));
    }

    dijk();

    cout << dist[n];

    return 0;
}