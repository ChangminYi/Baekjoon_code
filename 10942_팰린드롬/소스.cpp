#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> argi;
vector<vector<bool>> is_palin;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    argi.resize(n + 1);
    is_palin.resize(n + 1, vector<bool>(n + 1, false));
    for (int i = 1; i <= n; i++) {
        cin >> argi[i];
        is_palin[i][i] = true;  // 길이 1의 수열은 반드시 팰린드롬
    }
    cin >> m;

    // 연속하는 같은 두 수는 팰린드롬
    for (int i = 1; i < n; i++) {
        if (argi[i] == argi[i + 1]) {
            is_palin[i][i + 1] = true;
        }
    }
    // 나머지 팰린드롬 업데이트
    for (int i = 2; i < n; i++) {
        for (int j = 1; j <= n - i; j++) {
            if (argi[j] == argi[j + i] && is_palin[j + 1][j + i - 1]) {
                is_palin[j][j + i] = true;
            }
        }
    }

    do {
        int lo, hi;
        cin >> lo >> hi;

        cout << (is_palin[lo][hi] ? 1 : 0) << '\n';
    } while (--m > 0);

    return 0;
}