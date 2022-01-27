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
    * ������ �����̳� ���� �� �ʿ䰡 ���� C�� ����.
    * nCr = n! / (r! * (n-r)!)�̴�. ���丮���� �̸� n���� ���ϰ�,
    * �丣���� ������, a^p-2 mod p�� �̿��Ͽ� ������ ������ ���Ѵ�.
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