#include <iostream>
#include <cmath>

using namespace std;

long long n, m;
long long lo = 1, hi = 1, mid, ans;
long long arg[100'000];

bool do_test(const long long t) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += t / arg[i];
    }

    return sum >= m;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 한 입국심사대가 처리할 수 있는 사람은 시간/인당 처리시간.
    * 따라서 시간에 대하여 모든 입국심사대의 처리량의 합을 구하면
    * 시간 내에 모든 사람이 통과할 수 있는지 알 수 있다.
    * 시간을 매개변수로 하여 이분탐색을 진행하면 된다.
    */

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> arg[i];
        hi = max(hi, arg[i] * m);
    }

    while (lo <= hi) {
        mid = (lo + hi) / 2;
        if (do_test(mid)) {
            ans = mid;
            hi = mid - 1;
        }
        else {
            lo = mid + 1;
        }
    }

    cout << ans;

    return 0;
}