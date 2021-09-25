#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

typedef long long lli;
typedef pair<int, int> pint;
typedef pair<lli, int> pq_n;

int n, m;
vector<vector<pint>> graph;
vector<lli> min_dist;
vector<bool> updated;
priority_queue<pq_n, vector<pq_n>, greater<pq_n>> pq;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    graph.resize(n + 1);
    min_dist.resize(n + 1);
    updated.resize(n + 1, false);

    /*
    * 다익스트라 응용
    * 그래프에는 자신의 쌍과 결과물의 아이템 번호 저장
    * 초기에 모든 cost를 pq에 넣고 시작.
    * 만약 업데이트 가능한 아이템 있으면 업데이트하고,
    * 결과를 pq에 push하여 계속 업데이트.
    */
    for (int i = 1; i <= n; i++) {
        cin >> min_dist[i];
        pq.push(pq_n(min_dist[i], i));
    }
    for (int i = 0, dst, s1, s2; i < m; i++) {
        cin >> dst >> s1 >> s2;
        graph[s1].push_back(pint(s2, dst));
        graph[s2].push_back(pint(s1, dst));
    }

    while (!pq.empty()) {
        int cur = pq.top().second;
        pq.pop();

        if (!updated[cur]) {
            updated[cur] = true;

            for (const pint& edge : graph[cur]) {
                int cur_pair = edge.first;
                int nxt = edge.second;

                if (updated[cur_pair] && min_dist[cur] + min_dist[cur_pair] < min_dist[nxt]) {
                    min_dist[nxt] = min_dist[cur] + min_dist[cur_pair];
                    pq.push(pq_n(min_dist[nxt], nxt));
                }
            }
        }
    }

    cout << min_dist[1];

    return 0;
}