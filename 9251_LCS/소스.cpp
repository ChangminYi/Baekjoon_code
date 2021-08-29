#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main(void) {
    cin.tie(nullptr);
    cin.sync_with_stdio(false);
    cout.tie(nullptr);
    cout.sync_with_stdio(false);

    string a, b;
    cin >> a >> b;

    vector<vector<int>> lcs(a.size() + 1, vector<int>(b.size() + 1, 0));
    for (int i = 1; i <= a.size(); i++) {
        for (int j = 1; j <= b.size(); j++) {
            if (a[i - 1] == b[j - 1]) {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            }
            else {
                lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
            }

        }
    }

    cout << lcs.back().back();

    return 0;
}