#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	//lcs 길이 먼저 구하고
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

	//역순으로 문자열 구하기
    string res = "";
    int i = a.size(), j = b.size();
    while (true) {
        if (res.size() == lcs.back().back()) {
            break;
        }
        else {
            if (i > 0 && lcs[i][j] == lcs[i - 1][j]) {
                i--;
            }
            else if (j > 0 && lcs[i][j] == lcs[i][j - 1]) {
                j--;
            }
            else {
                res = a[i - 1] + res;
                i--; j--;
            }
        }
    }

    cout << lcs.back().back() << '\n' << res;

	return 0;
}