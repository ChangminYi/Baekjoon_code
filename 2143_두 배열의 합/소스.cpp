#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long lli;

int sum_to_find, n, m;
vector<int> a, b, sum1, sum2;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> sum_to_find;
    cin >> n;
    a.resize(n);
    for (int &i : a) {
        cin >> i;
    }
    cin >> m;
    b.resize(m);
    for (int &i : b) {
        cin >> i;
    }

    for (int i = 0, tmp_sum; i < n; i++) {
        tmp_sum = 0;

        for (int j = i; j < n; j++) {
            tmp_sum += a[j];
            sum1.push_back(tmp_sum);
        }
    }
    for (int i = 0, tmp_sum; i < m; i++) {
        tmp_sum = 0;
        
        for (int j = i; j < m; j++) {
            tmp_sum += b[j];
            sum2.push_back(tmp_sum);
        }
    }
    sort(sum2.begin(), sum2.end());

    lli res = 0;
    for (const int& cur : sum1) {
        int diff = sum_to_find - cur;

        auto upper = upper_bound(sum2.begin(), sum2.end(), diff);
        auto lower = lower_bound(sum2.begin(), sum2.end(), diff);
        res += distance(lower, upper);
    }

    cout << res;

    return 0;
}