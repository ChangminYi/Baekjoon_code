#include <iostream>
#include <numeric>

using namespace std;

typedef long long lli;
typedef pair<int, int> pint;

const int MAX = 1000000000;

int testcase, k, c;

pint ext_gcd(int a, int b) {
    if (b == 0) {
        return pint(1, 0);
    }
    else {
        pint res = ext_gcd(b, a % b);
        return pint(res.second, res.first - (a / b) * res.second);
    }
}

lli mod_inv(int a, int p) {
    return (ext_gcd(a, p).first + (lli)p) % p;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * Ȯ�� ��Ŭ���� �˰���. cx = 1(mod k)�� ��츦 ã�� ����.
    * ���� k�� c�� ���μҰ� �ƴ϶��, ���ǿ� �´� �ظ� ���� �� ����.
    * ���μ��� ��쿡��, �������� ���Ͽ� ���ǿ� �°� �� ���.
    */
    cin >> testcase;
    do {
        cin >> k >> c;

        if (gcd(k, c) == 1) {
            lli res = mod_inv(c, k);

            while (res * c <= k) {
                res += k;
            }

            res > MAX ? cout << "IMPOSSIBLE\n" : cout << res << '\n';
        }
        else {
            cout << "IMPOSSIBLE\n";
        }
    } while (--testcase);

    return 0;
}