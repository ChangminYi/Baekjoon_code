#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <numeric>

using namespace std;

struct pqn {
    int node, dist;
    pqn(const int _n = 0, const int _d = 0) : node(_n), dist(_d) {}
    bool operator>(const pqn& other) const { return this->dist > other.dist; }
};

const int INF = INT32_MAX / 2;

int n, m;
vector<int> graph[501];
int dist[501][501];
priority_queue<pqn, vector<pqn>, greater<pqn>> pq;

void dijk(const int start) {
    fill(dist[start] + 1, dist[start] + n + 1, INF);
    dist[start][start] = 0;
    pq.push(pqn(start, 0));
    while (!pq.empty()) {
        int cur = pq.top().node;
        int cur_dist = pq.top().dist;
        pq.pop();

        if (cur_dist <= dist[start][cur]) {
            for (const int nxt : graph[cur]) {
                int new_dist = cur_dist + 1;
                if (new_dist < dist[start][nxt]) {
                    dist[start][nxt] = new_dist;
                    pq.push(pqn(nxt, new_dist));
                }
            }
        }
    }
}

bool can_know_all(const int cur) {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (i != cur) {
            if (dist[i][cur] != INF || dist[cur][i] != INF) {
                cnt++;
            }
        }
    }
    return cnt == n - 1;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 사람 간의 키를 잰 것을 방향이 있는 간선으로 취급한다.
    * 간선의 가중치는 편리성을 고려하여 1로 설정.
    * 플로이드-와샬이나 다익스트라를 통해 전체 노드에 대한 전체 거리를 구하고,
    * 각각의 노드에 대해서 자신을 제외하고, 거리가 무한대가 아닌 노드를 찾는다.
    * 자신의 정확한 순위를 아는 것은, 모든 사람에 대해서 이동 가능하다는 것.
    * 따라서 카운트가 n-1개이면 자신의 정확한 순위를 알 수 있는 것이다.
    */
    cin >> n >> m;
    for (int i = 0, a, b; i < m; i++) {
        cin >> a >> b;
        graph[a].push_back(b);
    }

    for (int i = 1; i <= n; i++) {
        dijk(i);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (can_know_all(i)) ans++;
    }

    cout << ans;

    return 0;
}