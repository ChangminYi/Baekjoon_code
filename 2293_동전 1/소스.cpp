#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int n, k;
vector<int> arg, dp;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    
    cin >> n >> k;
    arg.resize(n);
    dp.resize(k + 1);
    for (int& i : arg) {
        cin >> i;
    }

    /*
    * 0�� ���� �� �ִ� ����, ��� ���� ���� �ʴ� 1������ ���.
    * �������� �ڽ� ������ ���� ��쳢�� ���ϸ� ��������.
    */
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = arg[i]; j <= k; j++) {
            dp[j] += dp[j - arg[i]];
        }
    }

    cout << dp[k];

    return 0;
}