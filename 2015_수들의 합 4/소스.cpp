#include <iostream>
#include <vector>
#include <map>

using namespace std;

int n, k;
vector<long long> sum;
map<long long, long long> dp;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k;
    sum.resize(n);

    /*
    * �̸� ù ��° ���Һ����� �������� ���Ѵ�.
    * �׸���, ù ��°������ �������� ���鼭
    * k�� ���� �� �ִ� ������ ������ �� ���� ��� ���Ѵ�.
    */
    cin >> sum[0];
    for (int i = 1, tmp; i < n; i++) {
        cin >> tmp;
        sum[i] = sum[i - 1] + tmp;
    }

    long long cnt = 0;
    for (int i = 0; i < n; i++) {
        if (sum[i] == k) {
            cnt++;
        }

        cnt += dp[sum[i] - k];
        dp[sum[i]]++;
    }

    cout << cnt;

    return 0;
}