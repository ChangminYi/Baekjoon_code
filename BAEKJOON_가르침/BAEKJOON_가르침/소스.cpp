#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#define  MAX_STRING 50
#define  NUM_ALPHA 26

int n = 0;
int k = 0;
int result = 0;
bool visit[NUM_ALPHA] = { false };
string str[MAX_STRING];

void search(int alpha, int cnt) {
    if (cnt == k) {
        int temp_res = 0;

        for (int i = 0; i < n; i++) {
            bool can_read = true;

            for (int j = 0; j < str[i].length(); j++)
                if (!visit[str[i][j] - 'a']) {
                    can_read = false;
                    break;
                }

            if (can_read) {
                temp_res++;
            }
        }

        result = max(result, temp_res);
    }
    else {
        for (int i = alpha; i < NUM_ALPHA; i++) {
            if (!visit[i]) {
                visit[i] = true;
                search(i, cnt + 1);
                visit[i] = false;
            }
        }
    }

    return;
}

int main(void) {
    cin.tie(nullptr);
    cin.sync_with_stdio(false);
    cout.tie(nullptr);
    cout.sync_with_stdio(false);

    cin >> n >> k;

    if (k < 5) {
        result = 0;
    }
    else if (k == 26) {
        result = n;
    }
    else {
        for (int i = 0; i < n; i++) {
            cin >> str[i];
            str[i] = str[i].substr(4, str[i].length() - 8);
        }

        k -= 5;
        vector<int> pre_check = { 0, 2, 8, 13, 19 };
        for (int& i : pre_check) {
            visit[i] = true;
        }

        search(0, 0);
    }

    cout << result;

    return 0;
}