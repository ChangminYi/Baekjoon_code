#include <iostream>
#include <vector>

using namespace std;

typedef long long lli;

const int MAX = 1000000;

int testcase;
vector<lli> dp(MAX + 1, 1);

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * �̸� ������� ���� ���ϰ� ����.
    * i�� ������� �ݵ�� i�� ����� �����Ƿ�, �ʱ� dp���� �� ���Ѵ�.
    * �� ��, �������� ���ϱ� ���� �ٷ� ���� ���� �ڽſ��� ���Ѵ�.
    */
    for (int i = 2; i <= MAX; i++) {
        for (int j = i; j <= MAX; j += i) {
            dp[j] += i;
        }
    }
    for (int i = 1; i < MAX; i++) {
        dp[i + 1] += dp[i];
    }


    cin >> testcase;
    for (int i = 0, tmp; i < testcase; i++) {
        cin >> tmp;
        cout << dp[tmp] << '\n';
    }

    return 0;
}