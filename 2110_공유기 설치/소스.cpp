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

    // �Է��� ���� ���¶�� ������ �� ����.
    sort(arg.begin(), arg.end());

    /*
    * �Ű����� Ž��. ������ �������� �Ÿ��� ����.
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