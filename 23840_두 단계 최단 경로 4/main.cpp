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

const long long INF = INT64_MAX / 2;

int n, m, p, sp, ep;
vector<edge> graph[100001];
int points[21];
long long dist[21][100001], dp[1 << 21][21];

void dijk(const int start_idx) {
    priority_queue<pqn, vector<pqn>, greater<>> pq;
    fill(dist[start_idx] + 1, dist[start_idx] + n + 1, INF);
    
    dist[start_idx][points[start_idx]] = 0;
    pq.push(pqn(points[start_idx], 0));
    while(!pq.empty()) {
        int cur = pq.top().node;
        long long cur_dist = pq.top().dist;
        pq.pop();

        if(cur_dist > dist[start_idx][cur]) continue;
        for(const edge& adj: graph[cur]) {
            if(cur_dist + adj.cost >= dist[start_idx][adj.node]) continue;
            dist[start_idx][adj.node] = cur_dist + adj.cost;
            pq.push(pqn(adj.node, dist[start_idx][adj.node]));
        }
    }
}

int main() {
    /**
     * 다익스트라를 사용하여 시작점과 중간 정점에서의 최단거리를 구한다.
     * 비트마스킹을 이용하여 방문 상태와 현재 노드를 저장한다.
     * 모든 중간 정점을 경유했을 때 도착지로의 최단 거리를 구하고
     * 도착할 수 없으면 -1 출력하고 아니면 최단거리를 출력하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    for(int u, v, w; m--; ) {
        cin >> u >> v >> w;
        graph[u].push_back(edge(v, w));
        graph[v].push_back(edge(u, w));
    }
    cin >> sp >> ep >> p;
    p++;
    points[0] = sp;
    for(int i = 1, tmp; i < p; i++)
        cin >> points[i];

    for(int i = 0; i < p; i++)
        dijk(i);

    for(int i = 0; i < (1 << p); i++)
        fill(dp[i], dp[i] + p, INF);
    dp[1][0] = 0;
    for(int visit = 1; visit < (1 << p); visit += 2) {
        for(int nxt = 0; nxt < p; nxt++) {
            for(int cur = 0; cur < p; cur++) {
                if(dp[visit][cur] == INF || (visit & (1 << nxt)) || dist[cur][points[nxt]] == INF) continue;
                dp[visit | (1 << nxt)][nxt] = min(dp[visit | (1 << nxt)][nxt], dp[visit][cur] + dist[cur][points[nxt]]);
            }
        }
    }

    long long min_dist = INF;
    for(int i = 1; i < p; i++) {
        if(dist[i][ep] == INF) continue;
        min_dist = min(min_dist, dp[(1 << p) - 1][i] + dist[i][ep]);
    }

    cout << (min_dist == INF ? -1 : min_dist);

    return 0;
}