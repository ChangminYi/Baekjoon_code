#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<long long>> mat;

const long long MOD = 1'000'003;

int n, s, e, t;
char tmp;
mat orig, init;

mat operator*(const mat& lhs, const mat& rhs) {
    mat ret = mat(lhs.size(), vector<long long>(lhs.size(), 0));
    for (int i = 0; i < (int)lhs.size(); i++) {
        for (int j = 0; j < (int)lhs.size(); j++) {
            for (int k = 0; k < (int)lhs.size(); k++) {
                ret[i][j] += lhs[i][k] * rhs[k][j];
                ret[i][j] %= MOD;
            }
        }
    }
    return ret;
}

mat fast_exp(vector<vector<long long>> m, int exp) {
    if (exp == 0) {
        return init;
    }
    else {
        mat ret = fast_exp(m, exp / 2);
        return (exp & 1 ? ret * ret * m : ret * ret);
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 인접행렬에서 가중치가 주어진 경우, 길이가 1인 간선으로 연결된
    * 더미 노드들을 생성하여 인접 행렬을 구성하면 된다. 길의 수를
    * 구하는 것은 행렬의 분할 제곱으로 구하면 된다.
    */

    cin >> n >> s >> e >> t;
    init = mat(5 * n + 1, vector<long long>(5 * n + 1, 0));
    orig = mat(5 * n + 1, vector<long long>(5 * n + 1, 0));
    for (int i = 1; i <= 5 * n; i++) {
        init[i][i] = 1;
    }

    for (int i = 1, val; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> tmp;
            val = tmp - '0';
            if (val >= 1) {
                orig[5 * i][5 * j - val + 1] = 1;
            }
        }
        for (int j = 1; j < 5; j++) {
            orig[5 * (i - 1) + j][5 * (i - 1) + j + 1] = 1;
        }
    }

    cout << fast_exp(orig, t)[5 * s][5 * e];

    return 0;
}