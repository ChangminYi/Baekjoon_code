#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
string src, ans;
vector<vector<int>> dp;

bool comp(const char& s, const char& a) {
    if (s == 'i') {
        return a == 'i' || a == 'j' || a == 'l';
    }
    else if (s == 'v') {
        return a == 'v' || a == 'w';
    }
    else {
        return s == a;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 편집 거리 알고리즘인 levenshtein 알고리즘을 사용.
    * 문자 비교는 조건에 맞게 함수를 구현.
    */

    cin >> n >> m >> src >> ans;
    dp = vector<vector<int>>(m + 1, vector<int>(n + 1));
    src = ' ' + src;
    ans = ' ' + ans;

    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;
    }
    for (int i = 0; i <= n; i++) {
        dp[0][i] = i;
    }
    for (int i = 1, tmp1, tmp2, tmp3; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            tmp1 = dp[i - 1][j] + 1;
            tmp2 = dp[i][j - 1] + 1;
            tmp3 = dp[i - 1][j - 1] + (comp(src[j], ans[i]) ? 0 : 1);
            dp[i][j] = min({ tmp1, tmp2, tmp3 });
        }
    }

    cout << dp[m][n];

    return 0;
}