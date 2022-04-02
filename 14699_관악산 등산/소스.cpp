#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const int NOT_VISIT = -1;

int n, m;
vector<int> graph[5'001];
int height[5'001], dp[5'001];

int dfs(const int cur) {
    if (dp[cur] == NOT_VISIT) {
        dp[cur] = 0;
        for (const int nxt : graph[cur]) {
            if (height[nxt] > height[cur]) {
                dp[cur] = max(dp[cur], dfs(nxt));
            }
        }
        dp[cur]++;
    }
    return dp[cur];
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * dfs를 실행하되, 완전탐색이 아니라 dp를 활용한다.
    * 현재 노드에서 갈 수 있는 가장 많은 노드 수를 구하면 된다.
    * 이를 저장하여 다른 노드에서 시작할 때도 활용하면 된다.
    */

    cin >> n >> m;
    fill(dp + 1, dp + n + 1, NOT_VISIT);
    for (int i = 1; i <= n; i++) {
        cin >> height[i];
    }
    for (int n1, n2; m; m--) {
        cin >> n1 >> n2;
        if (height[n1] < height[n2]) graph[n1].push_back(n2);
        else graph[n2].push_back(n1);
    }

    for (int i = 1; i <= n; i++) {
        cout << dfs(i) << '\n';
    }


    return 0;
}