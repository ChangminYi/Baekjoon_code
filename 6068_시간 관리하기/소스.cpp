#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

struct node {
    int len, bound;
    bool operator<(const node& other) const { return bound < other.bound; }
};

int n, ans = INT32_MAX;
node arg[1'000];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 일이 끝나는 시점 기준으로 정렬.
    * 그리고 직전까지 일의 시작해야 하는 시간과 일이 끝나는 시간 중
    * 작은 값에서 현재 일이 걸리는 시간을 빼면 현재 일을 시작해야
    * 하는 시간이 구해진다.
    */

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arg[i].len >> arg[i].bound;
    }

    sort(arg, arg + n);

    for (int i = n - 1; i >= 0; i--) {
        ans = min(ans, arg[i].bound);
        ans -= arg[i].len;
    }

    cout << (ans >= 0 ? ans : -1);

    return 0;
}