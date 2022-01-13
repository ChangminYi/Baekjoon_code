#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
int arg[200];
vector<int> dp;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * 가장 긴 증가하는 부분수열 문제. 순서대로 서 있는 번호와 섞여 있는 번호를 이어보면,
    * 다른 선분과 교차하는 선분의 수가 옮겨야 하는 아이의 수와 같다. 따라서 전체 인원에서
    * 가장 긴 증가하는 부분수열의 길이를 뺀 값이 정답.
    */
    cin >> n;
    for (int i = 0; i < n;  i++) {
        cin >> arg[i];
    }

    for (int i = 0; i < n; i++) {
        if (dp.empty() || dp.back() < arg[i]) {
            dp.push_back(arg[i]);
        }
        else {
            auto lb = lower_bound(dp.begin(), dp.end(), arg[i]);
            *lb = arg[i];
        }
    }

    cout << n - dp.size();

    return 0;
}