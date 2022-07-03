#include <iostream>
#include <algorithm>
#include <cmath>
#include <numeric>

using namespace std;

typedef long long lli;

int n;
lli arg[2][500000];

bool is_sqrt(const lli val) {
    lli tmp = sqrt(val);
    return tmp * tmp == val;
}

int main() {
    /**
     * 비내림차순으로 정렬된 수열과 원래 수열의 같은 위치의 값의 곱이
     * 모두 제곱수가 되어야 정렬이 가능하다. 두 수를 직접 곱하면 long long으로도
     * 표현 불가능한 범위가 나오므로, 두 수의 최대공약수로 값을 나눠주고,
     * 나뉜 두 값이 모두 제곱수인지 확인하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> arg[0][i];
        arg[1][i] = arg[0][i];
    }

    sort(arg[1], arg[1] + n);

    bool flag = true;
    for(int i = 0; i < n && flag; i++) {
        lli g = gcd(arg[0][i], arg[1][i]);
        arg[0][i] /= g, arg[1][i] /= g;

        if(!is_sqrt(arg[0][i]) || !is_sqrt(arg[1][i]))
            flag = false;
    }

    cout << (flag ? "YES" : "NO");

    return 0;
}
