#include <iostream>

using namespace std;

int n, arg[100][2], sum;
bool dp[50001];

int main() {
    /**
     * 배낭 문제를 해결하듯이 풀면 된다.
     * 만약 총 금액의 합이 홀수라면 반드시 나눌 수 없기 때문에 0을 출력한다.
     * 아니라면, 합의 절반을 만들 수 있는지를 확인하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);
    
    for(int tc = 0; tc < 3; tc++) {
        sum = 0;
        cin >> n;
        for(int i = 0; i < n; i++) {
            cin >> arg[i][0] >> arg[i][1];
            sum += arg[i][0] * arg[i][1];
        }

        if(sum & 1)
            cout << "0\n";
        else {
            fill(dp, dp + sum / 2 + 1, false);
            dp[0] = true;
            for(int i = 0; i < n; i++) {
                for(int j = sum / 2; j >= arg[i][0]; j--) {
                    if(dp[j - arg[i][0]]) {
                        for(int k = 0; k < arg[i][1] && j + k * arg[i][0] <= sum / 2; k++) {
                            dp[j + k * arg[i][0]] = true;
                        }
                    }
                }
            }

            cout << (dp[sum / 2] ? 1 : 0) << '\n';
        }
    }

    return 0;
}