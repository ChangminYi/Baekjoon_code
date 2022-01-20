#include <iostream>
#include <vector>

using namespace std;

typedef long long lli;
typedef vector<vector<lli>> matrix;

const lli MOD = 1000000007;

int t, n, d, m;
matrix board[100];

matrix operator*(const matrix& lhs, const matrix& rhs) {
    matrix ret = matrix(n, vector<lli>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                ret[i][j] += (lhs[i][k] * rhs[k][j]) % MOD;
                ret[i][j] %= MOD;
            }
        }
    }
    return ret;
}

void operator*=(matrix& lhs, const matrix& rhs) {
    lhs = lhs * rhs;
}

matrix fast_exp(const matrix& mat, int exp) {
    matrix ret = matrix(n, vector<lli>(n, 0));
    if (exp == 0) {
        for (int i = 0; i < n; i++) {
            ret[i][i] = 1;
        }
        return ret;
    }
    else {
        ret = fast_exp(mat, exp / 2);
        ret *= ret;
        return exp & 1 ? ret * mat : ret;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * ���� ����� ���Ͽ� ������ �� �ִ� ��� ����� ���� ���Ѵ�.
    * �ٸ�, ����� ��ȯ��Ģ�� �������� �����Ƿ�, t���� ��������� ��� ���� ��
    * �� ����� d/t�� �Ѵ�. �׸��� �����ִ� d%t���� ��������� ��� �����ָ�
    * d�� �Ŀ� ������ �� �ִ� ��� ����� ���� ���� �� �ִ�.
    */
    cin >> t >> n >> d;
    for (int i = 0, m, n1, n2, cnt; i < t; i++) {
        board[i] = matrix(n, vector<lli>(n, 0));
        cin >> m;
        for (int j = 0; j < m; j++) {
            cin >> n1 >> n2 >> cnt;
            n1--, n2--;
            board[i][n1][n2] = cnt;
        }
    }

    matrix ans = matrix(n, vector<lli>(n, 0));
    for (int i = 0; i < n; i++) {
        ans[i][i] = 1;
    }
    for (int i = 0; i < t; i++) {
        ans *= board[i];
    }
    ans = fast_exp(ans, d / t);
    for (int i = 0; i < d % t; i++) {
        ans *= board[i];
    }

    for (const vector<lli>& row : ans) {
        for (const lli& i : row) {
            cout << i << ' ';
        }
        cout << '\n';
    }

    return 0;
}