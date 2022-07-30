#include <iostream>
#include <cmath>
#include <stack>

using namespace std;

const int NOT_VISIT = -1;

int max_dist, n;
int dir[102], cost[102], dp[102], parent[102];
stack<int> trace;

int main() {
    /**
     * 입력으로 주어지는 각 정비소마다의 거리를 통해 정비소와 목표의 좌표를 구한다.
     * dp를 이용하여 특정 위치까지 가는 데 걸리는 최소 시간을 구한다.
     * 이 과정에서 어느 노드에서 정비를 받았는지를 parent 배열에 저장한다.
     * 그 후, 목표 지점부터 역추적을 하여 경유한 정비소를 모두 출력하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> max_dist >> n;
    cin >> dir[1];
    for(int i = 2, tmp; i <= n + 1; i++) {
        cin >> tmp;
        dir[i] = tmp + dir[i - 1];
    }
    for(int i = 1; i <= n; i++) {
        cin >> cost[i];
    }

    fill(dp + 1, dp + n + 2, NOT_VISIT);
    for(int i = 0; i <= n; i++) {
        for(int j = i + 1; j <= n + 1 && dir[j] - dir[i] <= max_dist; j++) {
            if(dp[j] == NOT_VISIT || dp[i] + cost[i] < dp[j]) {
                parent[j] = i;
                dp[j] = dp[i] + cost[i];
            }
        }
    }
    for(int cur = parent[n + 1]; cur != 0; cur = parent[cur]) {
        trace.push(cur);
    }

    cout << dp[n + 1] << '\n' << trace.size() << '\n';
    for(; !trace.empty(); trace.pop()) {
        cout << trace.top() << ' ';
    }

    return 0;
}