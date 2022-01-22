#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <numeric>

using namespace std;

struct pqn {
    int node = 0;
    long long dist = 0;
    pqn(int _n, long long _d) : node(_n), dist(_d) {}
    bool operator>(const pqn& other) const {
        return this->dist > other.dist;
    }
};

struct edge {
    int adj = 0, dist = 0;
    edge(int _a, int _d) : adj(_a), dist(_d) {}
};

const long long INF = INT64_MAX / 2;

int n, m;
vector<edge> graph[100001];
long long dist[2][100001];
priority_queue<pqn, vector<pqn>, greater<pqn>> pq;

void dijk() {
    fill(dist[0] + 1, dist[0] + n + 1, INF);
    fill(dist[1] + 1, dist[1] + n + 1, INF);

    dist[0][1] = 0;
    pq.push(pqn(1, 0));
    while (!pq.empty()) {
        int cur = pq.top().node;
        long long cur_dist = pq.top().dist;
        pq.pop();

        if (cur_dist <= dist[cur_dist & 1][cur]) {
            for (const edge& e : graph[cur]) {
                int nxt = e.adj;
                long long new_dist = cur_dist + e.dist;
                if (new_dist < dist[new_dist & 1][nxt]) {
                    dist[new_dist & 1][nxt] = new_dist;
                    pq.push(pqn(nxt, new_dist));
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 다익스트라 알고리즘을 사용하여 최단거리를 구한다.
    * 다만, 총 거리가 홀수일 때와 짝수일 때를 나눠서 구해야 하므로,
    * dist 배열을 2열을 사용하여 새로 계산한 거리가 홀수일 때와 짝수일 때를
    * 나눠서 값을 갱신한다. 시작점인 1번 노드는 1번 노드와의 거리가 0이므로,
    * 짝수 거리만 0으로 초기화한 후 탐색을 시작해야 한다.
    */
    cin >> n >> m;
    for (int i = 0, n1, n2, weight; i < m; i++) {
        cin >> n1 >> n2 >> weight;
        graph[n1].push_back(edge(n2, weight));
        graph[n2].push_back(edge(n1, weight));
    }

    dijk();

    for (int i = 1; i <= n; i++) {
        cout << (dist[1][i] == INF ? -1 : dist[1][i]) << ' ' << (dist[0][i] == INF ? -1 : dist[0][i]) << '\n';
    }

    return 0;
}