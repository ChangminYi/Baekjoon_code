#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct edge {
    int node, weight;
    edge(const int _n = 0, const int _w = 0) : node(_n), weight(_w) {}
};

struct pqn {
    int node, dist;
    pqn(const int _n, const int _d) : node(_n), dist(_d) {}
    bool operator>(const pqn& other) {
        return this->dist > other.dist;
    }
};

const int INF = INT32_MAX / 2;

int n, m, p, q;
int home[5'001];
vector<edge> graph[5'001];
int dist[5'001];

void dijk(const int start) {
    priority_queue<pqn, vector<pqn>, greater<>> pq;
    fill(dist, dist + n + 1, INF);

    dist[start] = 0;
    pq.push(pqn(start, 0));
    while (!pq.empty()) {
        int cur = pq.top().node;
        int cur_dist = pq.top().dist;
        pq.pop();

        if (cur_dist <= dist[cur]) {
            for (const edge& e : graph[cur]) {
                int new_dist = cur_dist + e.weight;
                if (new_dist < dist[e.node]) {
                    dist[e.node] = new_dist;
                    pq.push(pqn(e.node, new_dist));
                }
            }
        }
    }
}

int main() {
    /*
    * 더미 노드를 활용하면 다익스트라 한 번을 실행하여 최단거리를 찾을 수 있다.
    * 모든 편의점과 연결되는 더미 노드 0번을 시작점으로 하여, 최단거리 탐색.
    * 그리고 거리가 최소가 되는 집 후보를 고르면 된다.
    */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    for (int a, b, c; m > 0; m--) {
        cin >> a >> b >> c;
        graph[a].push_back(edge(b, c));
        graph[b].push_back(edge(a, c));
    }
    cin >> p >> q;
    for (int i = 0; i < p; i++) {
        cin >> home[i];
    }
    for (int i = 0, tmp; i < q; i++) {
        cin >> tmp;
        graph[0].push_back(edge(tmp, 0));
    }

    dijk(0);

    int idx = INT32_MAX;
    int min_dist = INT32_MAX;
    for (int i = 0; i < p; i++) {
        if (dist[home[i]] < min_dist || (dist[home[i]] == min_dist && home[i] < idx)) {
            idx = home[i];
            min_dist = dist[home[i]];
        }
    }

    cout << idx;

    return 0;
}