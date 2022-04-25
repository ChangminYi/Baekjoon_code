#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

struct edge {
    int node, weight;
    edge(const int _n = 0, const int _w = 0) : node(_n), weight(_w) {}
};

struct pqn {
    int node;
    long long dist;
    pqn(const int _n = 0, const long long _d = 0) : node(_n), dist(_d) {}
    bool operator>(const pqn& other) {
        return this->dist > other.dist;
    }
};

const long long INF = INT64_MAX/ 2;

int n, m, a, b, c;
vector<edge> graph[100'001];
long long dist[3][100'001];
priority_queue<pqn, vector<pqn>, greater<>> pq;

void dijk(int idx, int start) {
    long long* d = dist[idx];
    fill(d + 1, d + n + 1, INF);
    d[start] = 0;
    pq.push(pqn(start, 0));
    while (!pq.empty()) {
        int cur = pq.top().node;
        long long cur_dist = pq.top().dist;
        pq.pop();

        if (cur_dist <= d[cur]) {
            for (const edge& e : graph[cur]) {
                int nxt = e.node;
                long long new_dist = cur_dist + e.weight;
                if (new_dist < d[nxt]) {
                    d[nxt] = new_dist;
                    pq.push(pqn(nxt, new_dist));
                }
            }
        }
    }
}

int main() {
    /*
    * 간선이 양방향이므로, X->a, X->b, X->c의 최단거리는
    * a->X, b->X, c->의 최단거리와 같다.
    * 따라서 세 점 a, b, c를 기준으로 모든 노드의 최단거리를 구한다.
    * 그리고 조건을 만족하는 노드를 탐색하여 출력하면 된다.
    */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> a >> b >> c >> m;
    for (int d, e, l; m > 0; m--) {
        cin >> d >> e >> l;
        graph[d].push_back(edge(e, l));
        graph[e].push_back(edge(d, l));
    }

    dijk(0, a);
    dijk(1, b);
    dijk(2, c);

    int ans = 1;
    long long max_dist = min(dist[0][1], min(dist[1][1], dist[2][1]));
    for (int i = 2; i <= n; i++) {
        long long tmp_dist = min(dist[0][i], min(dist[1][i], dist[2][i]));
        if (tmp_dist > max_dist) {
            max_dist = tmp_dist;
            ans = i;
        }
    }

    cout << ans;

    return 0;
}