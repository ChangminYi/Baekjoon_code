#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int n, gcd_val;
vector<int> argi, divisor;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    argi.resize(n);
    for (int& i : argi) {
        cin >> i;
    }

    sort(argi.begin(), argi.end());

    /*
    * a = k1 * m + r
    * b = k2 * m + r
    * ...과 같은 식이기 때문에, a-b를 하면 a-b의 최대공약수 m을 찾을 수 있다.
    * 이를 모든 수에 대해서 계산하고, 최대공약수들의 최대공약수를 구하면
    * 최대의 m값이 구해진다. 이를 소인수분해하여 출력하면 된다.
    * 소인수분해도 시간이 걸리므로, sqrt(gcd)까지 계산하여 정렬 후 출력.
    */
    gcd_val = argi[1] - argi[0];
    for (int i = 1; i < n - 1; i++) {
        gcd_val = gcd(gcd_val, argi[i + 1] - argi[i]);
    }

    divisor.push_back(gcd_val);
    for (int i = 2; i * i <= gcd_val; i++) {
        if (gcd_val % i == 0) {
            divisor.push_back(i);

            if (i * i != gcd_val) {
                divisor.push_back(gcd_val / i);
            }
        }
    }

    sort(divisor.begin(), divisor.end());
    for (int& i : divisor) {
        cout << i << ' ';
    }


    return 0;
}