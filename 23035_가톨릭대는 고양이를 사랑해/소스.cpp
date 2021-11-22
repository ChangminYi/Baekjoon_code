#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

int n, m, t;
vector<pint> arg, dp;

bool cmp(const pint& lhs, const pint& rhs) {
    return (lhs.first <= rhs.first && lhs.second <= rhs.second);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> t;
    
    for (int i = 0, r, c; i < t; i++) {
        cin >> r >> c;

        if (r <= n && c <= m) {
            arg.push_back(pint(r, c));
        }
    }

    /*
    * O(nlogn)의 가장 긴 증가하는 부분수열 문제.
    * 가장 빠른 경로만을 사용해야 하므로, 현재 위치에서 다음 위치는
    * 다음 좌표가 현재 좌표보다 r, c값이 모두 크거나 같을 때,
    * 즉 cmp 함수가 true일 때만이다. 그리고, 이동경로는 언제나
    * 오른쪽 아니면 아래 방향이므로, pair의 정렬 방식을 이용하여
    * 가장 긴 수열을 만들 수 있도록 고양이의 좌표들을 정렬해준다.
    * 그 후에 가장 긴 증가하는 부분수열 길이를 구하면 된다.
    */
    sort(arg.begin(), arg.end());

    dp.push_back(arg[0]);
    for (size_t i = 1; i < arg.size(); i++) {
        if (cmp(dp.back(), arg[i])) {
            dp.push_back(arg[i]);
        }
        else {
            auto lb = lower_bound(dp.begin(), dp.end(), arg[i], cmp);
            *lb = arg[i];
        }
    }

    cout << dp.size();
    
    return 0;
}