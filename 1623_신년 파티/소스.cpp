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
    * dfs�� �ϸ鼭, dp�� �ִ��� �����ϸ� �ȴ�.
    * �ڽ��� �����ϸ�, �ڽ��� ���Ӻ��ϴ� �ݵ�� �������� �ʴ´�.
    * �ڽ��� �������� �ʴ´ٸ�, �ڽ��� ���Ӻ��ϴ� ������ ���� �ְ�, �ƴ� ���� �ִ�.
    * ����, ������ �����ϴ� ���� ���� �ʴ� ��쿡 ���ؼ�
    * dp�� ���� �����ϸ鼭 �����ϴ� �ο��� ���ϸ� �ȴ�.
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