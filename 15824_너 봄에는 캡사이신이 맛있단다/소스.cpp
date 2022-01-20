#include <iostream>
#include <algorithm>

using namespace std;

typedef long long lli;

const lli MOD = 1000000007;

int n;
int arg[300000];

lli fast_exp(int base, int exp) {
    if (exp == 0) {
        return 1;
    }
    else {
        lli ret = fast_exp(base, exp >> 1);
        ret = (ret * ret) % MOD;
        ret *= exp & 1 ? base : 1;
        return ret % MOD;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * arg를 오름차순으로 정렬한다. arg 내의 임의의 값 x에 대해서,
    * x보다 작은 수가 i개 있고, x보다 큰 수가 j개 있다면,
    * 특정 조합 내에서 x가 최대인 경우의 수는 2^i, x가 최소인 경우는 2^j개 존재한다.
    * 따라서 모든 x에 대해서 (2^i - 2^j) * x를 구하여 더하면
    * 스코빌 지수의 합을 구할 수 있다.
    */
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arg[i];
    }
    sort(arg, arg + n);

    lli ans = 0;
    for (int i = 0; i < n; i++) {
        lli lower_cnt = fast_exp(2, i);
        lli upper_cnt = fast_exp(2, n - i - 1);
        ans += (arg[i] * lower_cnt) % MOD;
        ans -= (arg[i] * upper_cnt) % MOD;
        while (ans < 0) {
            ans += MOD;
        }
        ans %= MOD;
    }

    cout << ans;

    return 0;
}