#include <iostream>
#include <vector>

using namespace std;

typedef long long lli;

const lli MOD = 1000000007;

int n, m, d;
vector<vector<lli>> adj;

vector<vector<lli>> operator*(const vector<vector<lli>>& lhs, const vector<vector<lli>>& rhs) {
    vector<vector<lli>> mat(n, vector<lli>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                mat[i][j] += lhs[i][k] * rhs[k][j];
                mat[i][j] %= MOD;
            }
        }
    }

    return mat;
}

void operator*=(vector<vector<lli>>& lhs, const vector<vector<lli>>& rhs) {
    vector<vector<lli>> tmp = lhs * rhs;
    lhs = tmp;
}

vector<vector<lli>> mult(const int d) {
    vector<vector<lli>> mat;

    if (d == 0) {
        mat = vector<vector<lli>>(n, vector<lli>(n, 0));
        for (int i = 0; i < n; i++) {
            mat[i][i] = 1;
        }
    }
    else {
        mat = mult(d / 2);
        mat *= mat;
        if (d & 1) {
            mat *= adj;
        }
    }

    return mat;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 본대 산책2 문제와 같지만, 간선 정보가 입력으로 들어오므로
    * 인접 행렬만 만들어서 행렬 곱셈을 하면 된다.
    */
    cin >> n >> m;
    adj = vector<vector<lli>>(n, vector<lli>(n, 0));
    for (int i = 0, n1, n2; i < m; i++) {
        cin >> n1 >> n2;
        n1--, n2--;
        adj[n1][n2] = adj[n2][n1] = 1;
    }
    cin >> d;

    cout << mult(d)[0][0];

    return 0;
}