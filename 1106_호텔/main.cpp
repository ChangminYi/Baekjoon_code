#include <iostream>
#include <cmath>

using namespace std;

int c, n, arg[20][2], dp[100001];

int main() {
    /**
     * dp 배열의 인덱스를 비용으로 설정한다. 그 때의 값은 해당 비용을
     * 사용하여 얻을 수 있는 최대 고객 수로 설정한다. 그 후 배낭 문제를 풀면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);
    
    cin >> c >> n;
    for(int i = 0; i < n; i++) {
        cin >> arg[i][0] >> arg[i][1];
    }

    for(int i = 0; i < n; i++) {
        for(int j = arg[i][0]; j <= 100000; j++) {
            dp[j] = max(dp[j], dp[j - arg[i][0]] + arg[i][1]);
        }
    }

    for(int i = 1; i <= 100000; i++) {
        if(dp[i] >= c) {
            cout << i;
            break;
        }
    }

    return 0;
}