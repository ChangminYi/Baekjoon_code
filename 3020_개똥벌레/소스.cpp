#include <iostream>
#include <algorithm>

using namespace std;

int n, h;
int max_cnt = INT32_MAX, same_cnt;
int arg[2][100'000];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 석순은 솟아나온 길이 기준, 종유석은 종유석의 가장 아래 높이를 기준으로 정렬한다.
    * 이분 탐색을 통해서 현재 높이로 날아가면서 파괴하는 석순과 종유석의 수를 센다.
    */

    cin >> n >> h;
    n /= 2;
    for (int i = 0, val_hi; i < n; i++) {
        cin >> arg[0][i] >> arg[1][i];
        arg[1][i] = h - arg[1][i] + 1;
    }

    sort(arg[0], arg[0] + n);
    sort(arg[1], arg[1] + n);

    for (int i = 1, lo_cnt, hi_cnt; i <= h; i++) {
        lo_cnt = n - (lower_bound(arg[0], arg[0] + n, i) - arg[0]);
        hi_cnt = upper_bound(arg[1], arg[1] + n, i) - arg[1];
        if (hi_cnt + lo_cnt < max_cnt) {
            max_cnt = hi_cnt + lo_cnt;
            same_cnt = 1;
        }
        else if (hi_cnt + lo_cnt == max_cnt) {
            same_cnt++;
        }
        else continue;
    }

    cout << max_cnt << ' ' << same_cnt;

    return 0;
}