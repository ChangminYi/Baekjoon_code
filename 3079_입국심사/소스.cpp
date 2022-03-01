#include <iostream>
#include <cmath>

using namespace std;

long long n, m;
long long lo = 1, hi = 1, mid, ans;
long long arg[100'000];

bool do_test(const long long t) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += t / arg[i];
    }

    return sum >= m;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * �� �Ա��ɻ�밡 ó���� �� �ִ� ����� �ð�/�δ� ó���ð�.
    * ���� �ð��� ���Ͽ� ��� �Ա��ɻ���� ó������ ���� ���ϸ�
    * �ð� ���� ��� ����� ����� �� �ִ��� �� �� �ִ�.
    * �ð��� �Ű������� �Ͽ� �̺�Ž���� �����ϸ� �ȴ�.
    */

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> arg[i];
        hi = max(hi, arg[i] * m);
    }

    while (lo <= hi) {
        mid = (lo + hi) / 2;
        if (do_test(mid)) {
            ans = mid;
            hi = mid - 1;
        }
        else {
            lo = mid + 1;
        }
    }

    cout << ans;

    return 0;
}