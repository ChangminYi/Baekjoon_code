#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

typedef pair<int, int> pint;

int n, m;
set<int> elem;
vector<vector<pint>> graph;
vector<vector<int>> dp;
vector<int> degree;
queue<int> que;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    graph.resize(n + 1);
    degree.resize(n + 1, 0);

    for (int i = 0, x, y, k; i < m; i++) {
        cin >> x >> y >> k;

        degree[x]++;
        graph[y].push_back(pint(x, k));
    }

    /*
    * degree가 0이라면 기본 부품이므로, 큐에 삽입하고
    * 기본 부품 목록에 올린다.
    */
    for (int i = 1; i <= n; i++) {
        if (degree[i] == 0) {
            que.push(i);
            elem.insert(i);
        }
    }

    /*
    * dp테이블 초기화. column의 크기는 기본 부품의 수
    */
    dp.resize(n + 1, vector<int>(elem.size(), 0));
    for (auto i = elem.begin(); i != elem.end(); i++) {
        dp[*i][distance(elem.begin(), i)] = 1;
    }

    /*
    * 위상 정렬로 부품 수 세기
    * 연결된 다음 부품에 자신의 부품 수 * 필요 수량 모두 더한다.
    * degree가 0이 되면 큐에 삽입하여 반복.
    */
    while (!que.empty()) {
        int cur = que.front();
        que.pop();

        for (const pint& edge : graph[cur]) {
            int nxt = edge.first;

            for (int i = 0; i < (int)elem.size(); i++) {
                dp[nxt][i] += dp[cur][i] * edge.second;
            }

            if (--degree[nxt] == 0) {
                que.push(nxt);
            }
        }
    }

    for (auto i = elem.begin(); i != elem.end(); i++) {
        cout << *i << ' ' << dp[n][distance(elem.begin(), i)] << '\n';
    }

    return 0;
}