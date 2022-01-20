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
    * arg�� ������������ �����Ѵ�. arg ���� ������ �� x�� ���ؼ�,
    * x���� ���� ���� i�� �ְ�, x���� ū ���� j�� �ִٸ�,
    * Ư�� ���� ������ x�� �ִ��� ����� ���� 2^i, x�� �ּ��� ���� 2^j�� �����Ѵ�.
    * ���� ��� x�� ���ؼ� (2^i - 2^j) * x�� ���Ͽ� ���ϸ�
    * ���ں� ������ ���� ���� �� �ִ�.
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