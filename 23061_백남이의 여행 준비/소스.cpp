#include <iostream>
#include <vector>

using namespace std;

int n, m, limit_bag = 0;
vector<int> weight, value, bag;
int dp[101][1000001];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    weight.resize(n + 1);
    value.resize(n + 1);
    bag.resize(m + 1);

    for (int i = 1; i <= n; i++) {
        cin >> weight[i] >> value[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> bag[i];
        limit_bag = max(limit_bag, bag[i]);
    }

    /*
    * 배낭 문제.
    * 물건을 n개까지 사용했을 때 limit_bag의 최댓값을 구하면,
    * dp[n]에는 0부터 limit_bag까지의 무게에서의 최댓값이 모두 있음.
    * 이를 활용하여 결과를 계산하면 됨.
    */
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= limit_bag; j++) {
            if (j < weight[i]) {
                dp[i][j] = dp[i - 1][j];
            }
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
            }
        }
    }

    /*
    * 물품 가치가 0이 나올 수 있음
    * 그러니까 초기화를 음수로 해야 함.
    */
    double max_pri = -1;
    int idx = 0;
    for (int i = 1; i <= m; i++) {
        double tmp_pri = (double)dp[n][bag[i]] / bag[i];

        if (max_pri < tmp_pri) {
            idx = i;
            max_pri = tmp_pri;
        }
    }

    cout << idx;

    return 0;
}