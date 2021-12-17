#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <numeric>

using namespace std;

struct pqn {
    int node = 0, dist = 0;
    pqn(const int _n, const int _d) : node(_n), dist(_d) {}
    bool operator>(const pqn& other) const {
        return this->dist > other.dist;
    }
};

const int INF = INT32_MAX / 2;

int n, m;
vector<int> graph[101];
int dist[101][101];
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
            for (const int& nxt : graph[cur]) {
                int new_dist = cur_dist + 1;
                if (new_dist < dist[start][nxt]) {
                    dist[start][nxt] = new_dist;
                    pq.push(pqn(nxt, new_dist));
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    for (int heavy, light; m > 0; m--) {
        cin >> heavy >> light;
        graph[light].push_back(heavy);
    }

    for (int i = 1; i <= n; i++) {
        dijk(i);
    }

    /*
    * 특정 노드에서 다른 노드에 도달할 수 있는지를 보면 된다.
    * 전체 노드에 대해서 최단거리를 구하고, 두 노드 중 한 방향이라도
    * 도달할 수 있으면 카운트해준다. 모두 구하여 전체 노드 수에서 뺀 값을
    * 출력하면 그 값이 도달할 수 없는 노드의 수.
    */
    for (int i = 1, reachable; i <= n; i++) {
        reachable = 0;
        for (int j = 1; j <= n; j++) {
            if (dist[i][j] != INF || dist[j][i] != INF) {
                reachable++;
            }
        }

        cout << n - reachable << '\n';
    }

    return 0;
}