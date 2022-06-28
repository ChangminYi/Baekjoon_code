#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct pqn {
    int node;
    long long dist;
    pqn(const int _n, const long long _d) : node(_n), dist(_d) {}
    bool operator>(const pqn& other) {
        return dist > other.dist;
    }
};

const long long INF = INT64_MAX / 2;

int n, m, k, s, cost[2];
long long dist[100'001];
bool can_visit[100'001], is_danger[100'001];
vector<int> graph[100'001];
queue<int> que;
priority_queue<pqn, vector<pqn>, greater<>> pq;

int main() {
    /**
     * 다익스트라를 통해 최단거리를 구하기 전, 위험 구역을 bfs로 먼저 구한다. 
     * 그 후, 다익스트라를 실행한다. 좀비가 점령한 곳은 방문하지 않는다.
     * n번째 노드에서는 숙박하지 않으므로, n번째 노드의 최단거리에서 숙박비를 빼야 한다.
     * 최단 거리의 범위가 int를 넘어갈 수 있다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> k >> s >> cost[0] >> cost[1];
    fill(can_visit + 1, can_visit + n + 1, true);
    fill(dist + 1, dist + n + 1, INF);
    for(int i = 0, node; i < k; i++) {
        cin >> node;
        can_visit[node] = false;
        dist[node] = 0;
        que.push(node);
    }
    for(int i = 0, n1, n2; i < m; i++) {
        cin >> n1 >> n2;
        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
    }

    while(!que.empty()) {
        int cur = que.front();
        que.pop();

        if(dist[cur] < s) {
            for(const int& nxt: graph[cur]) {
                if(dist[nxt] == INF) {
                    is_danger[nxt] = true;
                    dist[nxt] = dist[cur] + 1;
                    que.push(nxt);
                }
            }
        }
    }

    fill(dist + 1, dist + n + 1, INF);
    dist[1] = 0;
    pq.push(pqn(1, 0));
    while(!pq.empty()) {
        int cur = pq.top().node;
        long long cur_dist = pq.top().dist;
        pq.pop();

        if(cur_dist <= dist[cur]) {
            for(const int& nxt: graph[cur]) {
                if(can_visit[nxt]) {
                    long long new_dist = cur_dist + (is_danger[nxt] ? cost[1] : cost[0]);
                    if(new_dist < dist[nxt]) {
                        dist[nxt] = new_dist;
                        pq.push(pqn(nxt, new_dist));
                    }
                }
            }
        }
    }

    cout << dist[n] - (is_danger[n] ? cost[1] : cost[0]);

    return 0;
}