#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

int n, m;
int diff = INT32_MAX;
vector<int> argi;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0, tmp; i < n; i++) {
        cin >> tmp;
        argi.push_back(tmp);
    }
    sort(argi.begin(), argi.end());

    /*
    * 정렬 후, 차이가 m-1을 초과하는 값을 찾음.
    * 없으면 더 이상 탐색할 필요가 없으므로 루프를 탈출하고,
    * 있다면 두 수 차이를 업데이트.
    */
    for (int i = 0; i < n; i++) {
        auto ub = upper_bound(argi.begin() + i, argi.end(), argi[i] + m - 1);
        
        if (ub == argi.end()) {
            break;
        }
        else {
            diff = min(diff, *ub - argi[i]);
        }
    }

    cout << diff;

    return 0;
}