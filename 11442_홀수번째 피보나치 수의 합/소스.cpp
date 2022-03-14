#include <iostream>
#include <array>

using namespace std;

typedef array<long long, 2> row;
typedef array<row, 2> mat;

const long long MOD = 1'000'000'007;

long long n;
mat power_0 = {
    row({1, 0}),
    row({0, 1})
};
mat power_1 = {
    row({1, 1}),
    row({1, 0})
};

mat operator*(const mat& lhs, const mat& rhs) {
    mat ret = {
        row({ 0, 0 }),
        row({ 0, 0 })
    };
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                ret[i][j] += lhs[i][k] * rhs[k][j];
                ret[i][j] %= MOD;
            }
        }
    }
    return ret;
}

mat exp_pow(mat m, long long n) {
    if (n == 0) return power_0;
    else {
        mat ret = exp_pow(m, n / 2);
        ret = ret * ret;
        return (n & 1 ? ret * m : ret);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 피보나치 수의 점화식을 분해해보면, 홀수 번째 피보나치 수의 합은
    * n보다 크거나 같은 가장 작은 짝수의 피보나치 수와 같다.
    * 따라서 행렬 곱셈을 분할 정복으로 구현하여 값을 구하면 된다.
    */

    cin >> n;
    if (n & 1) n++;

    cout << exp_pow(power_1, n)[0][1];

    return 0;
}