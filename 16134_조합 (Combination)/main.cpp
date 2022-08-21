#include <iostream>

using namespace std;

long long MOD = 1000000007;

int n, r;
long long fact[1000001], inv[1000001];

long long fast_exp(long long a, long long p) {
    long long ret = 1;
    while(p) {
        if(p & 1) ret = (ret * a) % MOD;
        a = (a * a) % MOD;
        p >>= 1;
    }
    return ret;
}

int main() {
    /**
     * 모듈로 곱셈 역원을 사용하면 빠르게 조합을 구할 수 있다.
     * 팩토리얼을 계산하고, 팩토리얼 값의 곱셈 역원을 구하면 된다.
     * 모듈로 곱셈 역원은 a^(p - 2) = a^-1 (mod p)임을 이용하여 구한다.
     * mod 값이 매우 크므로 분할 정복을 통해 곱셈을 하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> r;
    fact[0] = 1;
    for(int i = 1; i <= n; i++)
        fact[i] = fact[i - 1] * i % MOD;
    inv[n] = fast_exp(fact[n], MOD - 2);
    for(int i = n - 1; i >= 0; i--)
        inv[i] = inv[i + 1] * (i + 1) % MOD;

    cout << (((fact[n] * inv[r]) % MOD) * inv[n - r]) % MOD;

    return 0;
}
