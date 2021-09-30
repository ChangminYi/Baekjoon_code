#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <limits>

using namespace std;

typedef pair<int, int> pint;

constexpr int INF = INT32_MAX / 2;

int n, m;
vector<vector<int>> graph;
vector<vector<int>> min_weight, max_weight, dist;
priority_queue<pint, vector<pint>, greater<pint>> pq;

void dijk(int start) {
    dist[start][start] = 0;
    pq.push(pint(0, start));

    while (!pq.empty()) {
        int cur = pq.top().second;
        int cur_dist = pq.top().first;
        pq.pop();

        if (cur_dist <= dist[start][cur]) {
            for (const int& nxt : graph[cur]) {
                int new_dist = cur_dist + min_weight[cur][nxt];
                int old_dist = dist[start][nxt];

                if (new_dist < old_dist) {
                    dist[start][nxt] = new_dist;
                    pq.push(pint(new_dist, nxt));
                }
            }
        }
    }
}

double get_burning_time() {
    double min_t = INF;
    
    /*
    * i번 정점에 불을 붙인다.
    */
    for (int i = 1; i <= n; i++) {
        double max_t = 0;

        /*
        * j번 정점에서 인접한 k번 정점으로 불이 번진다.
        * 불이 번지는 시간은 최단거리인 dist[i][k] - dist[i][j]이다.
        * 최대 간선 길이에서 최단거리를 빼면 남은 불타는 시간이 나오고,
        * k번 정점도 불이 붙어 간선이 반대 방향에서도 불타므로
        * 2로 나눠준 값이 최장 간선이 불타는 시간이 된다.
        * 이 값에 dist[i][k]를 더하면 i번 정점에 불을 붙였을 때
        * k번 정점까지 불타는 시간이 된다.
        * 그 값들 중 최댓값이 그래프 전체가 불타는 시간이 된다.
        */
        for (int j = 1; j <= n; j++) {
            for (const int& k : graph[j]) {
                int remain_len = max_weight[j][k] - (dist[i][k] - dist[i][j]);

                if (remain_len > 0) {
                    double spend_t = remain_len / 2.0 + dist[i][k];
                    max_t = max(spend_t, max_t);
                }
            }
        }

        min_t = min(max_t, min_t);
    }

    return min_t;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    graph.resize(n + 1);
    min_weight.resize(n + 1, vector<int>(n + 1, INF));
    max_weight.resize(n + 1, vector<int>(n + 1, 0));
    dist.resize(n + 1, vector<int>(n + 1, INF));

    /*
    * 최단거리 구할 때 쓸 min_weight과
    * 불타는 시간 구할 때 쓸 max_weight 저장.
    */
    for (int i = 0, n1, n2, w; i < m; i++) {
        cin >> n1 >> n2 >> w;

        if (min_weight[n1][n2] == INF) {
            graph[n1].push_back(n2);
            graph[n2].push_back(n1);

            min_weight[n1][n2] = min_weight[n2][n1] = w;
            max_weight[n1][n2] = max_weight[n2][n1] = w;
        }
        else {
            min_weight[n1][n2] = min_weight[n2][n1] = min(min_weight[n2][n1], w);
            max_weight[n1][n2] = max_weight[n2][n1] = max(max_weight[n2][n1], w);
        }
    }

    /*
    * 전체 최단 거리 구하기.
    * 다익스트라 n번 돌렸다.
    */
    for (int i = 1; i <= n; i++) {
        dijk(i);
    }

    (cout << fixed).precision(1);
    cout << get_burning_time();

    return 0;
}