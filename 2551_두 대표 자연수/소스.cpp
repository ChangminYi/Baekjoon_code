#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

typedef long long lli;

constexpr int LO = 1;
constexpr int HI = 10000;

int n;
vector<lli> argi_sum, pow_sum;
vector<int> argi;

int get_first_val() {
    lli ans = INT64_MAX;
    int pos = 0;

    for (int i = 1; i <= n; i++) {
        lli sum = (i - 1LL) * argi[i] - argi_sum[i - 1]
            + argi_sum[n] - argi_sum[i]
            - ((lli)n - i) * argi[i];

        if (ans > sum) {
            ans = sum;
            pos = i;
        }
    }

    return argi[pos];
}

lli get_second_val() {
    lli ans = INT64_MAX;
    int pos = 0;

    for (int i = argi[1]; i <= argi[n]; i++) {
        lli sum = pow_sum[n] - 2LL * i * argi_sum[n] + (lli)n * i * i;

        if (ans > sum) {
            ans = sum;
            pos = i;
        }
    }

    return pos;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    argi.resize(n + 1);
    argi_sum.resize(n + 1);
    pow_sum.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> argi[i];
    }

    sort(argi.begin() + 1, argi.end());
    for (int i = 1; i <= n; i++) {
        argi_sum[i] = argi_sum[i - 1] + argi[i];
        pow_sum[i] = pow_sum[i - 1] + (lli)argi[i] * argi[i];
    }

    cout << get_first_val() << ' ' << get_second_val();

    return 0;
}