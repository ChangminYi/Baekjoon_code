#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

long long x, y, d, t;
double dist, ans;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> x >> y >> d >> t;

    /*
    * 거리를 구한 다음, 점프를 할 수 있는 횟수 계산.
    * 그리고 최대한 점프하면 남는 거리 계산.
    */
    dist = sqrt(x * x + y * y);
    ans = dist;
    long long remain = dist / d;
    dist -= remain * d;

    if (remain == 0) {
        /*
        * 한 번 점프하여 돌아오거나, 두 번 점프
        */
        ans = min({ans, (double)t + d - dist, 2.0 * t});
    }
    else {
        /*
        * remain번 점프 하여 남은 거리 걸어가거나, 한 번 더 점프하여 돌아서 가기
        */
        ans = min({ ans, (double)remain * t + dist, (double)(remain + 1) * t });
    }

    (cout << fixed).precision(13);
    cout << ans;

    return 0;
}