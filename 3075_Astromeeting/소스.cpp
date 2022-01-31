#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <cmath>

using namespace std;

struct pqn {
    int node;
    long long dist;
    pqn(const int _n, const long long _d) :node(_n), dist(_d) {}
    bool operator>(const pqn& other) const { return this->dist > other.dist; }
};

const long long INF = INT64_MAX / 2;

int t, n, p, q;
vector<int> adj[101];
int person_list[101];
int weight[101][101];
long long dist[101][101];
priority_queue<pqn, vector<pqn>, greater<pqn>> pq;

void dijk(const int start) {
    fill(dist[start] + 1, dist[start] + p + 1, INF);
    dist[start][start] = 0;
    pq.push(pqn(start, 0));
    while (!pq.empty()) {
        int cur = pq.top().node;
        long long cur_dist = pq.top().dist;
        pq.pop();

        if (cur_dist <= dist[start][cur]) {
            for (const int nxt : adj[cur]) {
                long long new_dist = cur_dist + weight[cur][nxt];
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

    /*
    * 생략된 조건이 있어서 조심해야 할 부분이 있음.
    * 한 노드에서 다른 노드로 연결된 간선이 유일하지 않은 경우가 있다.
    * 따라서, 최소의 가중치를 가지는 노드만 저장하면 된다.
    * 나머지는 전체 노드에 대한 전체 최소 거리를 구하여 제곱의 합이
    * 최소가 되는 노드의 번호를 찾으면 된다.
    */
    cin >> t;
    do {
        cin >> n >> p >> q;
        for (int i = 0; i < n; i++) {
            cin >> person_list[i];
        }
        for (int i = 1; i <= p; i++) {
            adj[i].clear();
            fill(weight[i] + 1, weight[i] + p + 1, INT32_MAX);
        }
        for (int i = 0, u, v, d; i < q; i++) {
            cin >> u >> v >> d;
            adj[u].push_back(v), adj[v].push_back(u);
            weight[v][u] = weight[u][v] = min(d, weight[u][v]);
        }

        for (int i = 0; i < n; i++) {
            dijk(person_list[i]);
        }

        int galax_num;
        long long dist_sum = INT64_MAX;
        for (int i = 1; i <= p; i++) {
            long long tmp_sum = 0;
            bool visit_avail = true;
            for (int j = 0; j < n; j++) {
                if (dist[person_list[j]][i] == INF) {
                    visit_avail = false;
                    break;
                }
                else {
                    tmp_sum += dist[person_list[j]][i] * dist[person_list[j]][i];
                }
            }

            if (visit_avail && tmp_sum < dist_sum) {
                galax_num = i, dist_sum = tmp_sum;
            }
        }

        cout << galax_num << ' ' << dist_sum << '\n';
    } while (--t);

    return 0;
}