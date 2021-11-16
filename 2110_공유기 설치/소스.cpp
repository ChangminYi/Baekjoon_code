#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, c;
vector<int> arg;

int get_cnt(int interval) {
    int ret = 1, base = arg[0];

    for (auto i = 1; i < n ; i++) {
        if (arg[i] >= base + interval) {
            base = arg[i];
            ret++;
        }
    }

    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> c;
    arg.resize(n);
    for (int& i : arg) {
        cin >> i;
    }

    // 입력이 정렬 상태라고 보장할 수 없음.
    sort(arg.begin(), arg.end());

    /*
    * 매개변수 탐색. 변수를 공유기의 거리로 설정.
    */
    int lo = 1, hi = arg[n - 1];
    int res = 0;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        int cnt = get_cnt(mid);

        if (cnt >= c) {
            res = max(res, mid);
            lo = mid + 1;
        }
        else {
            hi = mid - 1;
        }
    }

    cout << res;

    return 0;
}