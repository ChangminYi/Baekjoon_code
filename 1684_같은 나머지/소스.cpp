#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

int n;
int arg[1'000], sub[999];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 두 수의 차가 양수가 되도록 입력 배열을 정렬한다.
    * 정답은 인접한 배열의 값의 모든 차이값의 최대공약수이다.
    */

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arg[i];
    }
    sort(arg, arg + n);

    for (int i = 0; i < n - 1; i++) {
        sub[i] = arg[i + 1] - arg[i];
    }

    int ans = sub[0];
    for (int i = 1; i < n - 1; i++) {
        ans = gcd(ans, sub[i]);
    }

    cout << ans;

    return 0;
}