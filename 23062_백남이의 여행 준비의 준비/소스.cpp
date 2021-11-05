#include <iostream>
#include <numeric>

using namespace std;

typedef long long lli;

int testcase;
lli n[3], a[3];

// Ȯ�� ��Ŭ���� �˰���
lli ext_euclid(lli a, lli b, lli& x, lli& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    else {
        lli d = ext_euclid(b, a % b, y, x);
        y -= a / b * x;
        return d;
    }
}

// �߱����� ������ ����. �ذ� ������ -1.
lli crt(lli a, lli m, lli b, lli n) {
    if (n > m) {
        swap(a, b);
        swap(m, n);
    }

    lli x, y;
    lli g = ext_euclid(m, n, x, y);
    if (a % g != b % g) {
        return -1;
    }
    else {
        x = (b - a) % n * x % n / g * m + a;
        if (x < 0) {
            x += m / g * n;
        }

        return x;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> testcase;

    /*
    * �߱����� ������ ���� ����.
    * �ϴ� �� ���� ���ؼ� ���� ���� ����, �ذ� �����ϴ��� �Ǵ�.
    * �ذ� ������ ���� ������ �Ѿ��, �ذ� �ִٸ�
    * ���� �� ���� ����� �� ��° ���� �ٽ� �ظ� ����.
    */
    do {
        for (int i = 0; i < 3; i++) {
            cin >> n[i];
        }
        for (int i = 0; i < 3; i++) {
            cin >> a[i];
        }

        lli ret = crt(a[0], n[0], a[1], n[1]);
        if (ret < 0) {
            cout << -1 << '\n';
        }
        else {
            lli newmod = (n[0] / gcd(n[0], n[1])) * n[1];
            cout << crt(ret, newmod, a[2], n[2]) << '\n';
        }
    } while (--testcase);

    return 0;
}
