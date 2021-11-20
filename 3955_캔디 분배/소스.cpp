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
    * 확장 유클리드 알고리즘. cx = 1(mod k)인 경우를 찾는 문제.
    * 만약 k와 c가 서로소가 아니라면, 조건에 맞는 해를 가질 수 없다.
    * 서로소인 경우에만, 곱셈역을 구하여 조건에 맞게 답 출력.
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