#include <iostream>
#include <vector>

using namespace std;

typedef long long lli;

int n, m;
vector<vector<int>> graph;
vector<lli> init, dp;

void dfs(int cur) {
    /*
    * 부모로부터의 누적합
    */
    for (const int& child : graph[cur]) {
        dp[child] += dp[cur] + init[child];
        dfs(child);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    graph.resize(n + 1);
    init.resize(n + 1, 0);
    dp.resize(n + 1, 0);

    for (int i = 1, parent; i <= n; i++) {
        cin >> parent;
        if (parent != -1) {
            graph[parent].push_back(i);
        }
    }
    for (int i = 0, n, w; i < m; i++) {
        cin >> n >> w;
        init[n] += w;
    }

    /*
    * 루트 노드인 1번부터 dfs 실행.
    * dp 구축하고 출력하면 끝.
    */
    dfs(1);
    for (int i = 1; i <= n; i++) {
        cout << dp[i] << ' ';
    }

    return 0;
}