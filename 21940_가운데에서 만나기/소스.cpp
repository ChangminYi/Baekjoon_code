#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <numeric>
#include <cmath>

using namespace std;

struct pqn {
    int next_node = 0, cost = 0;
    pqn(int _n, int _c) : next_node(_n), cost(_c) {}
    bool operator>(const pqn& other) const {
        return this->cost > other.cost;
    }
};

const int INF = INT32_MAX / 2;

int n, m, k;
vector<int> graph[201], pos;
int weight[201][201], dist[201][201];
priority_queue<pqn, vector<pqn>, greater<pqn>> pq;

void dijk(const int start) {
    fill(dist[start] + 1, dist[start] + n + 1, INF);
    dist[start][start] = 0;
    pq.push(pqn(start, 0));

    while (!pq.empty()) {
        int cur = pq.top().next_node;
        int cur_dist = pq.top().cost;
        pq.pop();

        if (cur_dist <= dist[start][cur]) {
            for (const int& nxt : graph[cur]) {
                int new_dist = cur_dist + weight[cur][nxt];
                
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

    cin >> n >> m;
    for (int i = 0, n1, n2, w; i < m; i++) {
        cin >> n1 >> n2 >> w;
        graph[n1].push_back(n2);
        weight[n1][n2] = w;
    }
    cin >> k;
    for (int i = 0, tmp; i < k; i++) {
        cin >> tmp;
        pos.push_back(tmp);
    }

    for (int i = 1; i <= n; i++) {
        dijk(i);
    }

    /*
    * 플로이드-와샬 혹은 다익스트라로 전체 노드에 대한 전체 최단거리를 구함.
    * 루프롤 돌면서 목적지를 i로 설정했을 때, 한 인원이 가장 많이 이동하는 거리를 계산.
    * 이동 거리의 최댓값의 최솟값을 구하면 된다.
    */
    int min_dist = INF;
    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        bool all_go = true;
        int cur_max = 0;
        for (const int p : pos) {
            if (dist[i][p] != INF && dist[p][i] != INF) {
                cur_max = max(cur_max, dist[i][p] + dist[p][i]);
            }
            else {
                all_go = false;
                break;
            }
        }

        if (all_go) {
            if (cur_max < min_dist) {
                min_dist = cur_max;
                ans = vector<int>(1, i);
            }
            else if (cur_max == min_dist) {
                ans.push_back(i);
            }
        }
    }

    for (const int& i : ans) {
        cout << i << ' ';
    }

    return 0;
}