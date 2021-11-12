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
            * 만약 i번째의 일이 아직 할당이 안되었다면, 
            * idx번째의 사람에게 일을 재귀적으로 할당하고, 비용을 갱신한다.
            * dp 배열에는 할당한 일에 대한 최소 비용이 저장된다.
            * dp 배열의 인덱스는 비트마스킹으로 표현한 일의 할당 상태이다.
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

    // 비트마스킹 + dp. n이 크지 않아서 가능
    cout << init_dp(0, 0);

    return 0;
}