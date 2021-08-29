#include <iostream>

using namespace std;
typedef long long lli;

int main() {
    cin.tie(nullptr);
    cin.sync_with_stdio(false);
    cout.tie(nullptr);
    cout.sync_with_stdio(false);

    lli n = 0;
    cin >> n;

    lli ans = n;
    for (lli i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            ans -= ans / i;

            while (n % i == 0) {
                n /= i;
            }
        }
    }

    if (n > 1) {
        ans -= ans / n;
    }

    cout << ans;

    return 0;
}