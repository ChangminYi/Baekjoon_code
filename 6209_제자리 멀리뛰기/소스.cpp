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
    * 모든 돌섬을 밟아야 하기 때문에, 정렬된 좌표를 순서대로 밟아야 한다.
    * 건너뛰어야 하는 최소 거리를 매개변수로 하여, 이분탐색을 진행한다.
    * 거리 조건을 만족시키지 못한 돌이 m개 이하라면 거리를 더 늘려도 되고,
    * m개 초과라면 거리를 줄여야 한다.
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