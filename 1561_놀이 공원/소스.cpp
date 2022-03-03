#include <iostream>

using namespace std;

long long n, m;
long long arg[10'001];
long long lo, hi, mid, actual_time;

bool check_finish(const long long cur_time) {
    long long sum = m;
    for (int i = 1; i <= m; i++) {
        sum += cur_time / arg[i];
    }
    return sum >= n;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * �̺�Ž���� �Ͽ� ��� ����� ������ ������ �ð��� ���� �˾Ƴ��� �Ѵ�.
    * �׸���, ������ ���� �ð����� ������ ���� ����� ���� ����,
    * ������ �ð��� ź ����� �� ���� ���� ����� ���̱ⱸ ��ȣ�� ����ϸ� �ȴ�.
    */

    cin >> n >> m;
    
    if (n <= m) {
        cout << n;
    }
    else {
        for (int i = 1; i <= m; i++) {
            cin >> arg[i];
        }

        lo = 0, hi = 60'000'000'000;
        while (lo <= hi) {
            mid = (lo + hi) / 2;
            if (check_finish(mid)) {
                actual_time = mid;
                hi = mid - 1;
            }
            else {
                lo = mid + 1;
            }
        }

        long long finish_cnt = m;
        for (int i = 1; i <= m; i++) {
            finish_cnt += (actual_time - 1) / arg[i];
        }

        for (int i = 1; i <= m; i++) {
            if (actual_time % arg[i] == 0) {
                if (++finish_cnt == n) {
                    cout << i;
                    break;
                }
            }
        }
    }

    return 0;
}