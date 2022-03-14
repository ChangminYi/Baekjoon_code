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
    * �Ǻ���ġ ���� ��ȭ���� �����غ���, Ȧ�� ��° �Ǻ���ġ ���� ����
    * n���� ũ�ų� ���� ���� ���� ¦���� �Ǻ���ġ ���� ����.
    * ���� ��� ������ ���� �������� �����Ͽ� ���� ���ϸ� �ȴ�.
    */

    cin >> n;
    if (n & 1) n++;

    cout << exp_pow(power_1, n)[0][1];

    return 0;
}