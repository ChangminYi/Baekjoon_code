#include <iostream>
#include <vector>

using namespace std;

typedef long long lli;

int d;
const lli MOD = 1000000007;
const vector<vector<lli>> I = {
    {1, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 1}
};
const vector<vector<lli>> adj = {
    {0, 1, 1, 0, 0, 0, 0, 0},
    {1, 0, 1, 1, 0, 0, 0, 0},
    {1, 1, 0, 1, 1, 0, 0, 0},
    {0, 1, 1, 0, 1, 1, 0, 0},
    {0, 0, 1, 1, 0, 1, 1, 0},
    {0, 0, 0, 1, 1, 0, 0, 1},
    {0, 0, 0, 0, 1, 0, 0, 1},
    {0, 0, 0, 0, 0, 1, 1, 0}
};

/*
* 0: 정보과학관 -> 전산관(1), 미래관(2)
* 1: 전산관 -> 정보과학관(0), 미래관(2), 신양관(3)
* 2: 미래관 -> 정보과학관(0), 전산관(1), 신양관(3), 한경직기념관(4)
* 3: 신양관 -> 전산관(1), 미래관(2), 한경직기념관(4), 진리관(5)
* 4: 한경직기념관 -> 미래관(2), 신양관(3), 진리관(5), 형남공학관(6)
* 5: 진리관 -> 신양관(3), 한경직기념관(4), 학생회관(7)
* 6: 형남공학관 -> 한경직기념관(4), 학생회관(7)
* 7: 학생회관 -> 진리관(5), 형남공학관(6)
*/

vector<vector<lli>> operator*(const vector<vector<lli>>& lhs, const vector<vector<lli>>& rhs) {
    vector<vector<lli>> mat(8, vector<lli>(8, 0));
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < 8; k++) {
                mat[i][j] += lhs[i][k] * rhs[k][j];
                mat[i][j] %= MOD;
            }
        }
    }

    return mat;
}

vector<vector<lli>> mult(const int n) {
    vector<vector<lli>> mat;

    if (n == 0) {
        mat = I;
    }
    else {
        mat = mult(n / 2);
        mat = mat * mat;
        if (n % 2 == 1) {
            mat = mat * adj;
        }
    }

    return mat;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 인접 행렬의 d 제곱은, d번 움직여서 해당 노드에 도착할 수 있는
    * 경우의 수를 의미한다. 수가 매우 크므로, 행렬을 분할하여 곱셈.
    */
    cin >> d;

    cout << mult(d)[0][0];

    return 0;
}