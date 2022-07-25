#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

typedef pair<int, int> pint;

int n, d;
pint arg[100000];

int main() {
    /**
     * 가격의 차가 d 이상 벌어지면 안되므로, d 미만으로 유지하면서 값을 계산해야 한다.
     * 선물의 가격을 기준으로 정렬하고, 가능한 한 많은 선물의 만족도를 더하여 최댓값을 계산.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);
    
    cin >> n >> d;
    for(int i = 0; i < n; i++) {
        cin >> arg[i].first >> arg[i].second;
    }

    sort(arg, arg + n);

    long long max_val = arg[0].second, tmp_sum = arg[0].second;
    for(int lo = 0, hi = 1; hi < n; tmp_sum -= arg[lo++].second) {
        while(hi < n && arg[hi].first - arg[lo].first < d) {
            tmp_sum += arg[hi++].second;
        }
        max_val = max(max_val, tmp_sum);
    }

    cout << max_val;

    return 0;
}