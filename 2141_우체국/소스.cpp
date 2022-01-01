#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long lli;
typedef pair<int, int> pint;

int n;
lli right_sum = 0, left_sum = 0;
pint arg[100000];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;

    for (int i = 0; i < n;i++) {
        cin >> arg[i].first >> arg[i].second;
        right_sum += arg[i].second;
    }

    /*
    * 마을 번호가 정렬되지 않았을 수도 있으므로, 마을 순서대로 정렬한다.
    * 그 후, 마을의 좌측 누적합과 우측 누적합의 차를 비교하여, 차이가 가장
    * 적은 곳이 우체국이 들어가야 할 곳이다.
    */
    sort(arg, arg + n);

    lli diff = INT64_MAX;
    int idx = 0;
    for (int i = 0; i < n; i++) {
        left_sum += arg[i].second;
        lli tmp_diff = abs(right_sum - left_sum);
        right_sum -= arg[i].second;
        
        if (tmp_diff < diff) {
            idx = i;
            diff = tmp_diff;
        }
    }

    cout << arg[idx].first;

    return 0;
}