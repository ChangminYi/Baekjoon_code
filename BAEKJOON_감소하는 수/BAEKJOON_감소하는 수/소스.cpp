#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef long long lli;

const int MAX_SIZE = 10;

int n;
int cnt = 0;
bool ans_find = false;
bool is_end = false;
lli ans = 0;
vector<vector<int>> argi(MAX_SIZE, vector<int>(MAX_SIZE));

void dfs(lli start, lli cur, int digit) {
    if (!ans_find) {
        if (digit == 1) {
            if (!is_end) {
                is_end = true;
            }
            else {
                cnt++;
            }
        }
        else {
            for (lli i = (lli)digit - 2; i < start; i++) {
                dfs(i, cur + (lli)(i * pow(10, digit - 2)), digit - 1);
            }
        }

        if (cnt == n && !ans_find) {
            ans = cur;
            ans_find = true;
        }
    }

    return;
}

int main() {
    cin.tie(nullptr);
    cin.sync_with_stdio(false);
    cout.tie(nullptr);
    cout.sync_with_stdio(false);

    for (int i = 0; i < MAX_SIZE; i++) {
        argi[0][i] = 1;
    }
    for (int i = 1; i < MAX_SIZE; i++) {
        for (int j = i; j < MAX_SIZE; j++) {
            if (j == i) {
                argi[i][j] = 1;
            }
            else {
                for (int k = i - 1; k < j; k++) {
                    argi[i][j] += argi[i - 1][k];
                }
            }
        }
    }

    cin >> n;
    if (n == 0) {
        cout << 0;
    }
    else {
        lli start = 0;
        int digit = 0;
        bool in_range = false;

        for (int i = 0; i < MAX_SIZE && !in_range; i++) {
            for (int j = i; j < MAX_SIZE && !in_range; j++) {
                if (cnt + argi[i][j] > n) {
                    in_range = true;
                }
                else {
                    digit = i + 1;
                    start = (lli)j + 1;
                    cnt += argi[i][j];
                }
            }
        }

        lli cur = start * pow(10, digit - 1);
        if (n == 1022) {
            cur = 9876543210;
        }

        if (cnt == n) {
            if (cnt == 1023) {
                ans = -1;
            }
            else {
                ans = cur;
            }
        }
        else if (n > 1022) {
            ans = -1;
        }
        else{
            dfs(start, cur, digit);
        }

        cout << ans;
    }

    return 0;
}
