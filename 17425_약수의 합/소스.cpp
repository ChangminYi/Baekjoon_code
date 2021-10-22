#include <iostream>
#include <vector>

using namespace std;

typedef long long lli;

const int MAX = 1000000;

int testcase;
vector<lli> dp(MAX + 1, 1);

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 미리 약수들의 합을 구하고 들어간다.
    * i의 배수들은 반드시 i를 약수로 가지므로, 초기 dp값에 다 더한다.
    * 그 후, 누적합을 구하기 위해 바로 앞의 값을 자신에게 더한다.
    */
    for (int i = 2; i <= MAX; i++) {
        for (int j = i; j <= MAX; j += i) {
            dp[j] += i;
        }
    }
    for (int i = 1; i < MAX; i++) {
        dp[i + 1] += dp[i];
    }


    cin >> testcase;
    for (int i = 0, tmp; i < testcase; i++) {
        cin >> tmp;
        cout << dp[tmp] << '\n';
    }

    return 0;
}