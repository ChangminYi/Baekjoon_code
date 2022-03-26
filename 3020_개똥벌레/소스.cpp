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
    * ������ �ھƳ��� ���� ����, �������� �������� ���� �Ʒ� ���̸� �������� �����Ѵ�.
    * �̺� Ž���� ���ؼ� ���� ���̷� ���ư��鼭 �ı��ϴ� ������ �������� ���� ����.
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