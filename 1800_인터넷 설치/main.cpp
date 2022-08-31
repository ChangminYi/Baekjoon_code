#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct edge {
    int node, cost;
    edge(const int _n = 0, const int _c = 0) {
        node = _n, cost = _c;
    }
};

struct pqn {
    int node, dist;
    pqn(const int _n, const int _d) {
        node = _n, dist = _d;
    }
    bool operator>(const pqn& other) const {
        return dist > other.dist;
    }
};

const int INF = INT32_MAX / 2;

int n, p, k;
vector<edge> graph[1001];
int dist[1001];

bool dijk(const int max_cost) {
    priority_queue<pqn, vector<pqn>, greater<>> pq;
    fill(dist + 1, dist + n + 1, INF);

    dist[1] = 0;
    pq.push(pqn(1, 0));
    while(!pq.empty()) {
        int cur = pq.top().node;
        int cur_dist = pq.top().dist;
        pq.pop();

        if(cur_dist > dist[cur]) continue;
        for(const edge& e: graph[cur]) {
            int nxt = e.node;
            int new_dist = cur_dist + (e.cost > max_cost ? 1 : 0);
            if(new_dist < dist[nxt]) {
                dist[nxt] = new_dist;
                pq.push(pqn(nxt, new_dist));
            }
        }
    }

    return dist[n] <= k;
}

int main() {
    /**
     * 인터넷 선 중 가장 비싼 것의 가격으로 매개변수 탐색을 한다.
     * 다익스트라 알고리즘을 사용하여 최단거리를 구하는데,
     * 간선의 비용이 매개변수보다 크면 1, 아니면 0으로 설정하여
     * 최단거리를 매개변수보다 큰 간선의 최소 갯수로 설정한다.
     * 찾지 못하였을 경우에는 -1 출력하는 예외처리를 조심한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> p >> k;
    for(int u, v, c; p--; ) {
        cin >> u >> v >> c;
        graph[u].push_back(edge(v, c));
        graph[v].push_back(edge(u, c));
    }

    int ans = -1;
    int lo = 0, hi = 2000000;
    while(lo <= hi) {
        int mid = (lo + hi) / 2;
        if(dijk(mid)) {
            ans = mid;
            hi = mid - 1;
        }
        else lo = mid + 1;
    }

    cout << ans;

    return 0;
}