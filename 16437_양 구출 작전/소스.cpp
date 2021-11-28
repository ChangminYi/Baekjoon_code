#include <iostream>
#include <vector>
#include <bitset>
#include <cmath>

using namespace std;

typedef long long lli;

const int MAX = 123456;

int n;
vector<int> sheep, wolf;
vector<lli> dp;
vector<vector<int>> graph;
bitset<MAX + 1> visit;

void dfs(const int cur) {
    dp[cur] = sheep[cur];

    for (const int& nxt : graph[cur]) {
        if (!visit[nxt]) {
            visit[nxt] = true;
            dfs(nxt);

            dp[cur] += dp[nxt];
        }
    }

    dp[cur] = max(dp[cur] - wolf[cur], 0LL);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    visit.reset();
    graph.resize(n + 1);
    sheep.resize(n + 1, 0);
    wolf.resize(n + 1, 0);
    dp.resize(n + 1, 0);

    for (int i = 2; i <= n; i++) {
        char type;
        int num, adj;
        cin >> type >> num >> adj;

        type == 'S' ? sheep[i] = num : wolf[i] = num;
        graph[i].push_back(adj);
        graph[adj].push_back(i);
    }

    /*
    * dfs + 트리에서의 dp 문제.
    * 루트부터 깊이 우선 탐색을 진행하면서 dp 배열을 초기화하고,
    * 자식 노드에서 올 수 있는 양의 수를 모두 더한 다음,
    * 현재 노드의 늑대 수만큼 뺀 값과 0 중에 큰 값이
    * 현재 노드에 올 수 있는 모든 양의 수.
    */
    visit[1] = true;
    dfs(1);

    cout << dp[1];

    return 0;
}