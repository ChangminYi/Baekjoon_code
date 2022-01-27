#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <numeric>

using namespace std;

typedef long long lli;
struct edge {
    int adj_node, dist;
    edge(const int _adj = 0, const int _d = 0) : adj_node(_adj), dist(_d) {}
};
struct pqn {
    int node;
    lli dist;
    pqn(const int _n = 0, const lli _d = 0) : node(_n), dist(_d) {}
    bool operator>(const pqn& other) const { return this->dist > other.dist; }
};
struct pqn_w : public pqn {
    int idx;
    pqn_w(const int _n = 0, const lli _d = 0, const int _idx = 0) : pqn(_n, _d), idx(_idx) {}
};

const lli INF = INT64_MAX / 2;

int n, m, cnt = 0;
lli dist_fox[40001], dist_wolf[2][4001];
vector<edge> graph[4001];
priority_queue<pqn, vector<pqn>, greater<pqn>> pq_fox;
priority_queue<pqn_w, vector<pqn_w>, greater<pqn_w>> pq_wolf;

void dijk_fox() {
    fill(dist_fox + 1, dist_fox + n + 1, INF);
    dist_fox[1] = 0;
    pq_fox.push(pqn(1, 0));
    while (!pq_fox.empty()) {
        int cur = pq_fox.top().node;
        lli cur_dist = pq_fox.top().dist;
        pq_fox.pop();

        if (cur_dist <= dist_fox[cur]) {
            for (const edge& e : graph[cur]) {
                lli new_dist = cur_dist + e.dist;
                if (new_dist < dist_fox[e.adj_node]) {
                    dist_fox[e.adj_node] = new_dist;
                    pq_fox.push(pqn(e.adj_node, new_dist));
                }
            }
        }
    }
}

void dijk_wolf() {
    fill(dist_wolf[0] + 1, dist_wolf[0] + n + 1, INF);
    fill(dist_wolf[1] + 1, dist_wolf[1] + n + 1, INF);
    dist_wolf[0][1] = 0;
    pq_wolf.push(pqn_w(1, 0, 0));
    while (!pq_wolf.empty()) {
        int cur = pq_wolf.top().node;
        lli cur_dist = pq_wolf.top().dist;
        int cur_idx = pq_wolf.top().idx;
        pq_wolf.pop();

        if (cur_dist <= dist_wolf[cur_idx][cur]) {
            for (const edge& e : graph[cur]) {
                lli new_dist = cur_dist + (cur_idx == 0 ? e.dist / 2 : e.dist * 2);
                int nxt_idx = (cur_idx == 0 ? 1 : 0);
                if (new_dist < dist_wolf[nxt_idx][e.adj_node]) {
                    dist_wolf[nxt_idx][e.adj_node] = new_dist;
                    pq_wolf.push(pqn_w(e.adj_node, new_dist, nxt_idx));
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 다익스트라 알고리즘을 사용하여 최단거리를 찾는다.
    * 늑대의 거리를 구할 때 나누기 2가 사용되므로, 간선의 가중치를 2를 곱하여 저장한다.
    * 늑대는 빠르게 달릴 경우, 느리게 달릴 경우의 두 가지 거리를 저장한다.
    * 여우의 거리가 늑대의 두 거리의 최솟값보다 작은 경우만 센다.
    * 구현의 편리함을 위하여 우선순위 큐의 노드는 상속으로 만들었다.
    */
    cin >> n >> m;
    for (int i = 0, a, b, d; i < m; i++) {
        cin >> a >> b >> d;
        graph[a].push_back(edge(b, 2 * d));
        graph[b].push_back(edge(a, 2 * d));
    }

    dijk_fox();
    dijk_wolf();

    for (int i = 2; i <= n; i++) {
        if (dist_fox[i] < min(dist_wolf[0][i], dist_wolf[1][i])) {
            cnt++;
        }
    }
    cout << cnt;

    return 0;
}