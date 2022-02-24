#include <iostream>
#include <vector>

using namespace std;

long long l, r, x, y;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * �־����� ���� ���� ���Ѹ��� �ֱ� ������, ���ǿ� ���� �ʴ�
    * �Է��� �־����� ������ �ɷ����� �Ѵ�. ��� �߿� int��
    * �Ѿ�� ���� �����Ƿ� long long�� ���. ���� 1���� ���� ���
    * �� ���� ����ϰ�, �ƴ϶�� ������ ����Ѵ�.
    */

    cin >> l >> r >> x >> y;
    if (l > r) swap(l, r);
    if (x < 0) x = -x;

    if (2 * x <= r - l) {
        cout << "Unknwon Number\n";
    }
    else if (y < 0 || y >= x) {
        cout << "Unknwon Number\n";
    }
    else {
        vector<long long> cand;
        long long base;
        if ((l % x + x) % x == y) base = l;
        else if ((l % x + x) % x < y) base = l + y - (l % x + x) % x;
        else base = l + x - (l % x + x) % x - y;

        for (; base <= r; base += x) {
            if ((base % x + x) % x == y) cand.push_back(base);
        }

        if (cand.size() == 1) cout << cand[0] << '\n';
        else cout << "Unknwon Number\n";
    }

    return 0;
}