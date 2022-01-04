#include <iostream>
#include <algorithm>

using namespace std;

int d, n, m;
int stone[50002];

int do_hop(const int offset) {
    int cur = 0, cnt = 0;

    for (int i = 1; i < n + 2; i++) {
        if (stone[cur] + offset > stone[i]) {
            cnt++;
        }
        else {
            cur = i;
        }
    }

    return cnt;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * ��� ������ ��ƾ� �ϱ� ������, ���ĵ� ��ǥ�� ������� ��ƾ� �Ѵ�.
    * �ǳʶپ�� �ϴ� �ּ� �Ÿ��� �Ű������� �Ͽ�, �̺�Ž���� �����Ѵ�.
    * �Ÿ� ������ ������Ű�� ���� ���� m�� ���϶�� �Ÿ��� �� �÷��� �ǰ�,
    * m�� �ʰ���� �Ÿ��� �ٿ��� �Ѵ�.
    */
    cin >> d >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> stone[i];
    }
    stone[n + 1] = d;
    sort(stone, stone + n + 2);

    int ans = 0;
    int lo = 0, hi = d;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;

        if (do_hop(mid) <= m) {
            ans = mid;
            lo = mid + 1;
        }
        else {
            hi = mid - 1;
        }
    }

    cout << ans;

    return 0;
}