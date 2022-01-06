#include <iostream>
#include <numeric>

using namespace std;

long long a, d, l, r;
int inst, q;

long long get_sum() {
    long long start = a + (l - 1) * d;
    long long last = a + (r - 1) * d;
    long long len = r - l + 1;
    return ((start + last) * (len >> 1)) + (len & 1 ? ((start + last) >> 1) : 0);
}

long long get_gcd() {
    long long start = a + (l - 1) * d;
    return l == r ? start : gcd(start, d);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * ���� ���ϴ� ������ ���������� �� ������ ���.
    * �ִ����� ������ ���, d = 0�� ��� �ִ������� �����̴�.
    * �ƴ϶��, gcd(al, d)�� ����.
    */
    cin >> a >> d >> q;
    do {
        cin >> inst >> l >> r;
        cout << (inst == 1 ? get_sum() : get_gcd()) << '\n';
    } while (--q);

    return 0;
}