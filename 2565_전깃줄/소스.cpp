#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

int n;
pint arg[100];
vector<int> dp;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * 가장 긴 증가하는 부분수열 문제. 다만, 전선이 순서대로 들어오지 않으므로,
    * 좌측 순서와 우측 순서를 둘 다 받아 좌측 기준으로 정렬. 그 후 우측을 기준으로
    * 가장 긴 증가하는 부분수열의 길이를 구하고, 전깃줄 수에서 빼면 정답.
    */
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arg[i].first >> arg[i].second;
    }

    sort(arg, arg + n);

    for (int i = 0; i < n; i++) {
        if (dp.empty() || dp.back() < arg[i].second) {
            dp.push_back(arg[i].second);
        }
        else {
            auto lb = lower_bound(dp.begin(), dp.end(), arg[i].second);
            *lb = arg[i].second;
        }
    }

    cout << n - dp.size();

    return 0;
}