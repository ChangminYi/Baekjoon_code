#include <iostream>
#include <array>

using namespace std;

typedef long long lli;
typedef array<array<lli, 2>, 2> mat;

const lli MOD = 1000000000;

lli a, b;

mat mult(const mat lhs, const mat rhs) {
    mat ret = {0, 0, 0, 0};
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            for(int k = 0; k < 2; k++) {
                ret[i][j] += (lhs[i][k] * rhs[k][j]) % MOD;
                ret[i][j] %= MOD;
            }
        }
    }
    return ret;
}

mat fast_exp(const mat m, const lli exp) {
    if(exp == 0) return {1, 0, 0, 1};
    else if(exp == 1) return {1, 1, 1, 0};
    else {
        mat res = fast_exp(m, exp / 2);
        res = mult(res, res);
        if(exp % 2)
            res = mult(res, {1, 1, 1, 0});
        return res;
    }
}

int main() {
    /**
     * 피보나치 수의 1부터 n번째 항까지의 합은 n+2번째 피보나치 수이다.
     * 피보나치 수는 행렬 곱셈으로 빠르게 구할 수 있다.
     * 따라서, b+2번째 항에서 a+1번째 항을 뺀 후 모듈러 연산을 하면 된다.
     */
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);
    
    cin >> a >> b;
    mat res_high = fast_exp({1, 1, 1, 0}, b + 2);
    mat res_lo = fast_exp({1, 1, 1, 0}, a + 1);
    
    lli res = (res_high[1][0] - res_lo[1][0] + MOD) % MOD;
    cout << res;

    return 0;
}