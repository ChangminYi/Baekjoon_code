#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

int n;
pint arg[1000'000];

bool comp(const pint& lhs, const pint& rhs) {
    return lhs.second < rhs.second;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 과제 마감일을 기준으로 정렬한다. 가장 마지막 마감일부터 시작하여,
    * 과제의 소요 시간이 겹치는 경우, 더 일찍 시작해야 하므로 현재 일에서
    * 소요 일수를 빼준다. 아니라면, 두 과제는 상관이 없으므로
    * 더 일찍 시작하는 값으로 최신화해준다.
    */
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arg[i].first >> arg[i].second;
    }

    sort(arg, arg + n, comp);

    int ans = arg[n - 1].second - arg[n - 1].first;
    for (int i = n - 2; i >= 0; i--) {
        if (ans >= arg[i].second) ans = arg[i].second - arg[i].first;
        else ans -= arg[i].first;
    }

    cout << ans;

    return 0;
}