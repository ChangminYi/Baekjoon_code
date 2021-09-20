#include <iostream>
#include <cmath>

using namespace std;

int testcase, lo, hi;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> testcase;
    do {
        cin >> lo >> hi;
        int len = hi - lo;
        int sq = (int)sqrt(len);

        if (len == sq * sq) {
            cout << 2 * sq - 1 << '\n';
        }
        else if (sq * sq < len && len <= sq * sq + sq) {
            cout << 2 * sq << '\n';
        }
        else {
            cout << 2 * sq + 1 << '\n';
        }

    } while (--testcase > 0);

    return 0;
}