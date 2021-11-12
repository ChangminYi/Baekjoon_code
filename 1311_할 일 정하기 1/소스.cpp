#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

using namespace std;

const int NOT_VISIT = -1;

int n;
vector<int> dp;
vector<vector<int>> table;

int init_dp(int idx, int cur) {
    if (idx == n) {
        return 0;
    }
    else {
        if (dp[cur] == NOT_VISIT) {
            dp[cur] = INT32_MAX;

            /*
            * ���� i��°�� ���� ���� �Ҵ��� �ȵǾ��ٸ�, 
            * idx��°�� ������� ���� ��������� �Ҵ��ϰ�, ����� �����Ѵ�.
            * dp �迭���� �Ҵ��� �Ͽ� ���� �ּ� ����� ����ȴ�.
            * dp �迭�� �ε����� ��Ʈ����ŷ���� ǥ���� ���� �Ҵ� �����̴�.
            */
            for (int i = 0; i < n; i++) {
                if ((cur & (1 << i)) == 0) {
                    dp[cur] = min(dp[cur], init_dp(idx + 1, cur | (1 << i)) + table[idx][i]);
                }
            }
        }

        return dp[cur];
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;

    table.resize(n, vector<int>(n));
    dp.resize(1 << n, NOT_VISIT);
    
    for (vector<int>& row : table) {
        for (int& i : row) {
            cin >> i;
        }
    }

    // ��Ʈ����ŷ + dp. n�� ũ�� �ʾƼ� ����
    cout << init_dp(0, 0);

    return 0;
}