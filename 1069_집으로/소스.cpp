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
    * �Ÿ��� ���� ����, ������ �� �� �ִ� Ƚ�� ���.
    * �׸��� �ִ��� �����ϸ� ���� �Ÿ� ���.
    */
    dist = sqrt(x * x + y * y);
    ans = dist;
    long long remain = dist / d;
    dist -= remain * d;

    if (remain == 0) {
        /*
        * �� �� �����Ͽ� ���ƿ��ų�, �� �� ����
        */
        ans = min({ans, (double)t + d - dist, 2.0 * t});
    }
    else {
        /*
        * remain�� ���� �Ͽ� ���� �Ÿ� �ɾ�ų�, �� �� �� �����Ͽ� ���Ƽ� ����
        */
        ans = min({ ans, (double)remain * t + dist, (double)(remain + 1) * t });
    }

    (cout << fixed).precision(13);
    cout << ans;

    return 0;
}