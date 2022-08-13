#include <iostream>
#include <stack>
#include <cmath>

using namespace std;

const int NOT_VISIT = -1;

int n, dp[200001];
bool visit[200001];
stack<int> stk;

int get_nxt(int cur) {
    int ret = cur;
    while(cur) {
        ret += cur % 10;
        cur /= 10;
    }
    ret %= n;
    return ret == 0 ? n : ret;
}

int dfs(int cur) {
    if(dp[cur] != NOT_VISIT)
        return dp[cur];
    else {
        if(visit[cur]) {
            stack<int> cycle;
            while(true) {
                cycle.push(stk.top());
                stk.pop();
                if(cycle.top() == cur) break;
            }

            int cycle_size = cycle.size();
            while(!cycle.empty()) {
                dp[cycle.top()] = cycle_size;
                cycle.pop();
            }
        }
        else {
            visit[cur] = true;
            stk.push(cur);

            int tmp_ret = dfs(get_nxt(cur));
            if(dp[cur] == NOT_VISIT) {
                dp[cur] = tmp_ret + 1;
                stk.pop();
            }
        }

        return dp[cur];
    }
}

int main() {
    /**
     * dfs를 통해서 사이클을 판별한다. 간선이 단 한 개이므로, 사이클 내부의
     * 노드들은 최대 n번 이동할 수 있다. 사이클 외부의 노드들은 자신의 자식
     * 노드보다 한 칸 더 진행할 수 있다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;

    fill(dp + 1, dp + n + 1, NOT_VISIT);

    int ans = 0;
    for(int i = 1; i <= n; i++) {
        if(!visit[i]) ans = max(ans, dfs(i));
    }

    cout << ans;

    return 0;
}
