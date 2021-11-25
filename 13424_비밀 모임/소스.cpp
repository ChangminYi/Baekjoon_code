#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <numeric>

using namespace std;

typedef pair<int, int> pint;

const int INF = INT32_MAX / 2;

int testcase, n, m, k;
vector<vector<pint>> graph;
vector<vector<int>> dist;
vector<int> person;
priority_queue<pint, vector<pint>, greater<pint>> pq;

void dijk(int idx) {
    dist[idx][idx] = 0;
    pq.push(pint(0, idx));

    while (!pq.empty()) {
        int cur = pq.top().second;
        int cur_dist = pq.top().first;
        pq.pop();

        if (cur_dist <= dist[idx][cur]) {
            for (const pint& edge : graph[cur]) {
                int nxt = edge.first, weight = edge.second;
                int new_dist = cur_dist + weight;

                if (new_dist <= dist[idx][nxt]) {
                    dist[idx][nxt] = new_dist;
                    pq.push(pint(new_dist, nxt));
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> testcase;
    do {
        cin >> n >> m;
        graph = vector<vector<pint>>(n + 1);
        dist = vector<vector<int>>(n + 1, vector<int>(n + 1, INF));

        for (int i = 0, n1, n2, w; i < m; i++) {
            cin >> n1 >> n2 >> w;
            graph[n1].push_back(pint(n2, w));
            graph[n2].push_back(pint(n1, w));
        }

        cin >> k;
        person = vector<int>(k);
        for (int& i : person) {
            cin >> i;
            dijk(i);
        }

        /*
        * 다익스트라 알고리즘으로 사람이 있는 곳에서 각 노드로
        * 갈 수 있는 거리를 모두 계산. 그리고 거리 총합이 가장 작은
        * 노드 번호를 찾아서 출력하면 된다.
        */
        int min_dist = INT32_MAX;
        int min_idx = 0;
        for (int i = 1, tmp_sum; i <= n; i++) {
            tmp_sum = 0;
            for (const int& j : person) {
                tmp_sum += dist[j][i];
            }

            if (tmp_sum < min_dist) {
                min_dist = tmp_sum;
                min_idx = i;
            }
        }

        cout << min_idx << '\n';
    } while (--testcase);

    return 0;
}