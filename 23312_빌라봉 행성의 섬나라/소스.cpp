#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, q;
vector<int> ub, cnt;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    ub.resize(n + 1, 1);
    cnt.resize(n + 1, 0);

    /*
    * ������ �� ���� ���̴� ������ ������ ����̱� ������, Ʈ�� ����.
    * ���� ������ ���� ��ȣ�� �����Ͽ�, �ԷµǴ� ���� ������ ����.
    * �ʱ� ������ ������ �� ������ ��ü ��-�ٸ��� ���� ����.
    */
    for (int i = 1, sum = 1, total_land, bridge; i <= n; i++) {
        cin >> total_land >> bridge;

        sum += total_land;
        ub[i] = sum;
        cnt[i] = total_land - bridge;
        for (int j = 0, dummy1, dummy2; j < bridge; j++) {
            cin >> dummy1 >> dummy2;
        }
    }

    /*
    * �ٸ� ������ ���� ���� ���� ����. ����, �ڽ��� ���� ���� ���� ����.
    * �Է����� ������ �� ���� ������ ���� ������ �ҼӵǾ� ����.
    * ���� �ٸ��� �������� ���� ���� �þ��, ����Ǹ� �پ��.
    * �̺�Ž������ �ԷµǴ� ���� ������ �˻��� �� ����.
    */
    cin >> q;
    do {
        int inst, idx;
        cin >> inst;

        if (inst == 1) {
            cin >> idx;
            cout << cnt[idx] << '\n';
        }
        else {
            int arg1, arg2;
            cin >> arg1 >> arg2;

            idx = distance(ub.begin(), upper_bound(ub.begin(), ub.end(), arg1));
            inst == 2 ? cnt[idx]++ : cnt[idx]--;
        }
    } while (--q);

    return 0;
}