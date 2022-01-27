#include <stdio.h>

long long MOD = 1000000007;

int n, m;
long long fact[1000001];

long long fast_exp(long long base, long long exp) {
    long long ret = 1;
    while (exp) {
        if (exp & 1) ret = (ret * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return ret;
}

int main(void) {
    /*
    * 복잡한 컨테이너 등을 쓸 필요가 없어 C로 구현.
    * nCr = n! / (r! * (n-r)!)이다. 팩토리얼을 미리 n까지 구하고,
    * 페르마의 소정리, a^p-2 mod p를 이용하여 곱셈의 역원을 구한다.
    */
    scanf("%d %d", &n, &m);

    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }

    long long base = fast_exp(fact[m], MOD - 2) * fast_exp(fact[n - m], MOD - 2) % MOD;

    printf("%lld", (fact[n] * base) % MOD);

    return 0;
}