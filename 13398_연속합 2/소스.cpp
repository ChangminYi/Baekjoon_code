#include <iostream>
#include <cmath>

using namespace std;

int n;
int arg[100000];
int dp[100000][2];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arg[i];
    }

    /*
    * ���� ������ ���, �������� ���� ���� ����.
    * �������� ���� ���, ���������� ������+���簪 Ȥ�� ���簪.
    * ������ ���, ���������� ������ Ȥ�� ������ ���� ������+���簪.
    */
    int max_val = arg[0];
    dp[0][0] = arg[0], dp[0][1] = arg[0];
    for (int i = 1; i < n; i++) {
        dp[i][0] = max(dp[i - 1][0] + arg[i], arg[i]);
        dp[i][1] = max(dp[i - 1][0], dp[i - 1][1] + arg[i]);
        max_val = max(max_val, max(dp[i][0], dp[i][1]));
    }

    cout << max_val;

    return 0;
}