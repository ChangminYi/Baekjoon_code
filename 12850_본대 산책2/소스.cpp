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
* 0: �������а� -> �����(1), �̷���(2)
* 1: ����� -> �������а�(0), �̷���(2), �ž��(3)
* 2: �̷��� -> �������а�(0), �����(1), �ž��(3), �Ѱ�������(4)
* 3: �ž�� -> �����(1), �̷���(2), �Ѱ�������(4), ������(5)
* 4: �Ѱ������� -> �̷���(2), �ž��(3), ������(5), �������а�(6)
* 5: ������ -> �ž��(3), �Ѱ�������(4), �л�ȸ��(7)
* 6: �������а� -> �Ѱ�������(4), �л�ȸ��(7)
* 7: �л�ȸ�� -> ������(5), �������а�(6)
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
    * ���� ����� d ������, d�� �������� �ش� ��忡 ������ �� �ִ�
    * ����� ���� �ǹ��Ѵ�. ���� �ſ� ũ�Ƿ�, ����� �����Ͽ� ����.
    */
    cin >> d;

    cout << mult(d)[0][0];

    return 0;
}