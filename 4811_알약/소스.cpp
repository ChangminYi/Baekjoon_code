#include <iostream>

using namespace std;

int n;
long long dp[31][31];

void init_dp() {
    for (int i = 0; i <= 30; i++) {
        for (int j = i; j <= 30; j++) {
            if (i == 0) {
                dp[i][j] = 1;
            }
            else {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * w와 h로 표현할 수 있는 문장의 수를 찾으면 된다.
    * 2차원 배열에 행은 w의 수, 열은 h의 수로 하여,
    * dp[i][j] = dp[i-1][j] + dp[i][j-1], 즉,
    * h가 하나 부족한 문자열과 w가 하나 부족한 문자열의 수를 더한다.
    */
    init_dp();

    while (true) {
        cin >> n;
        if (n == 0) {
            break;
        }
        else {
            cout << dp[n][n] << '\n';
        }
    }

    return 0;
}