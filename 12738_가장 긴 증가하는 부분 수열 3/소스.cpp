#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> arg, dp;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    arg.resize(n);
    for (int& i : arg) {
        cin >> i;
    }

    /*
    * O(nlogn)의 가장 긴 증가하는 부분수열 문제.
    * dp의 길이가 곧 가장 긴 증가하는 부분수열의 길이.
    */
    dp.push_back(arg[0]);
    for (int i = 1; i < n; i++) {
        if (dp.back() < arg[i]) {
            dp.push_back(arg[i]);
        }
        else {
            auto lb = lower_bound(dp.begin(), dp.end(), arg[i]);
            *lb = arg[i];
        }
    }

    cout << dp.size();

    return 0;
}