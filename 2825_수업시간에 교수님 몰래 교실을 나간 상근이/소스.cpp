#include <iostream>
#include <string>

using namespace std;

typedef long long lli;

const int SIZE = 1024;
lli hash_c[SIZE] = { 0 };

int32_t main() {
    cin.tie(0);
    cin.sync_with_stdio(false);
    cout.tie(0);
    cout.sync_with_stdio(false);

    lli n = 0, cnt = 0;
    string temp;
    cin >> n;

    for (lli i = 0; i < n; i++) {
        cin >> temp;

        int idx = 0;
        for (char& c : temp) {
            idx |= 1 << (c - '0');
        }

        hash_c[idx]++;
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i & j) {
                cnt += hash_c[i] * hash_c[j];
            }
        }
    }

    cout << (cnt - n) / 2;

    return 0;
}