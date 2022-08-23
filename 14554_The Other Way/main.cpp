#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct edge {
    int node;
    long long cost;
    edge(const int _n = 0, const long long _c = 0) {
        node = _n, cost = _c;
    }
};

struct pqn {
    int node;
    long long dist;
    pqn(const int _n, const long long _d) {
        node = _n, dist = _d;
    }
    bool operator>(const pqn& other) const {
        return dist > other.dist;
    }
};

long long INF = INT64_MAX / 2;
long long MOD = 1000000009;

int n, m, s, e;
vector<edge> graph[300001];
long long dist[300001], cnt[300001];
priority_queue<pqn, vector<pqn>, greater<>> pq;

int main() {
    /**
     * 같은 노드를 잇는 같은 길이의 간선일지라도, 다른 간선으로 취급한다.
     * 최단거리로 도달할 수 있는 모든 경우의 수를 센다. 같은 최단거리라도
     * 각기 다른 간선을 통해 오기 때문이다. 최단거리가 갱신되면 경우의 수도 갱신한다.
     * 거리의 최댓값이 int 범위를 초과할 수 있으니 주의한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> m >> s >> e;
    for(int a, b, c; m--; ) {
        cin >> a >> b >> c;
        graph[a].push_back(edge(b, c));
        graph[b].push_back(edge(a, c));
    }

    fill(dist + 1, dist + n + 1, INF);
    dist[s] = 0, cnt[s] = 1;
    pq.push(pqn(s, 0));
    while(!pq.empty()) {
        int cur = pq.top().node;
        long long cur_dist = pq.top().dist;
        pq.pop();

        if(cur_dist > dist[cur]) continue;
        for(const edge& e: graph[cur]) {
            long long new_dist = cur_dist + e.cost;
            if(new_dist > dist[e.node]) continue;
            else if(new_dist == dist[e.node])
                cnt[e.node] = (cnt[e.node] + cnt[cur]) % MOD;
            else {
                dist[e.node] = new_dist;
                cnt[e.node] = cnt[cur];
                pq.push(pqn(e.node, new_dist));
            }
        }
    }

    cout << cnt[e];

	return 0;
}