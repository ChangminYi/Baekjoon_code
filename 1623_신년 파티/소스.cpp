#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <cmath>

using namespace std;

const int NOT_COMMING = 0;
const int IS_COMMING = 1;

int n;
int dp[2][200'001];
vector<int> child[200'001];
bool visit[200'001];
priority_queue<int, vector<int>, greater<>> trace_pq;

void dfs(const int cur) {
    for (const int chd : child[cur]) {
        dfs(chd);

        dp[IS_COMMING][cur] += dp[NOT_COMMING][chd];
        visit[cur] = true;

        if (dp[IS_COMMING][chd] >= dp[NOT_COMMING][chd]) {
            visit[chd] = true;
            dp[NOT_COMMING][cur] += dp[IS_COMMING][chd];
        }
        else {
            visit[chd] = false;
            dp[NOT_COMMING][cur] += dp[NOT_COMMING][chd];
        }
    }
}

void trace_dp(const int cur, const bool cur_visit) {
    if (cur_visit) {
        trace_pq.push(cur);
    }
    
    for (const int chd : child[cur]) {
        if (cur_visit || !visit[chd]) trace_dp(chd, false);
        else trace_dp(chd, true);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * dfs를 하면서, dp에 최댓값을 갱신하면 된다.
    * 자신이 참여하면, 자신의 직속부하는 반드시 참여하지 않는다.
    * 자신이 참여하지 않는다면, 자신의 직속부하는 참여할 수도 있고, 아닐 수도 있다.
    * 따라서, 사장이 참여하는 경우와 하지 않는 경우에 대해서
    * dp의 값을 추적하면서 참석하는 인원을 구하면 된다.
    */

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> dp[IS_COMMING][i];
    }
    for (int i = 2, par; i <= n; i++) {
        cin >> par;
        child[par].push_back(i);
    }

    dfs(1);

    cout << dp[IS_COMMING][1] << ' ' << dp[NOT_COMMING][1] << '\n';
    trace_dp(1, true);
    for (; !trace_pq.empty(); trace_pq.pop()) {
        cout << trace_pq.top() << ' ';
    }
    cout << "-1\n";
    trace_dp(1, false);
    for (; !trace_pq.empty(); trace_pq.pop()) {
        cout << trace_pq.top() << ' ';
    }
    cout << -1;

    return 0;
}