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
    * �賶 ����.
    * ������ n������ ������� �� limit_bag�� �ִ��� ���ϸ�,
    * dp[n]���� 0���� limit_bag������ ���Կ����� �ִ��� ��� ����.
    * �̸� Ȱ���Ͽ� ����� ����ϸ� ��.
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
    * ��ǰ ��ġ�� 0�� ���� �� ����
    * �׷��ϱ� �ʱ�ȭ�� ������ �ؾ� ��.
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