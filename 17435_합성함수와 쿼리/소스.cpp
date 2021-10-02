#include <iostream>
#include <vector>

using namespace std;

const int MAX_ROW = 500001;
const int MAX_COL = 22;

int n, q;
int dp[MAX_ROW][MAX_COL];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    /*
    * ��ҹ迭.
    * 2^i��° �θ� �̸� ���Ѵ�. �׸��� �� ��������
    * �� �迭�� ���� ���󰡸� log(n)�� �ð����⵵��
    * fn(x)�� ���� ã�� �� �ִ�.
    */
    for (int i = 1; i <= n; i++) {
        cin >> dp[i][0];
    }
    for (int j = 1; j < MAX_COL; j++) {
        for (int i = 1; i <= n; i++) {
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
        }
    }

    cin >> q;
    /*
    * �θ� ���ϴ� �κ�.
    * ���ڷ� ���� arg1�� ��Ʈ ������ ���Ƽ�
    * ���� 2^k ���� ������ �� ����ŭ ����
    */
    do {
        int arg1, arg2;
        cin >> arg1 >> arg2;

        for (int i = 0; arg1 > 0; i++, arg1 >>= 1) {
            if (arg1 & 1) {
                arg2 = dp[arg2][i];
            }
        }

        cout << arg2 << '\n';
    } while (--q > 0);

    return 0;
}