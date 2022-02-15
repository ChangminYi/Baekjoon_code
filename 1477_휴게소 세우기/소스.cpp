#include <iostream>
#include <algorithm>

using namespace std;

int n, m, l;
int dir[1'001];

bool do_visit(const int dist) {
    int cnt = 0;
    for (int i = 1, cur_dist; i < n + 2; i++) {
        cur_dist = dir[i] - dir[i - 1];
        if (cur_dist >= dist) {
            if (cur_dist % dist == 0) cnt += (cur_dist / dist) - 1;
            else cnt += cur_dist / dist;
        }
    }

    return cnt <= m;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * �̺� Ž���� �����Ѵ�. Ž���� �Ű������� �ްԼ� ���� �Ÿ��̴�.
    * Ư���� �Ÿ��� �����ϰ�, �� �Ÿ���ŭ �ްԼҸ� ��ġ�� �� �ִٸ�
    * �� ���� �Ÿ��� Ž���Ѵ�. �����ߴٸ� �Ÿ��� �÷��� Ž���Ѵ�.
    */

    cin >> n >> m >> l;
    dir[0] = 0;
    for (int i = 1; i <= n; i++) {
        cin >> dir[i];
    }
    dir[n + 1] = l;
    sort(dir, dir + n + 2);

    int ans;
    int lo = 1, hi = l, mid;
    while (lo <= hi) {
        mid = (lo + hi) / 2;
        if (do_visit(mid)) {
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