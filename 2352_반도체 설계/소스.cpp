#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<int> argi, res;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for (int i = 0, tmp; i < n; i++) {
        cin >> tmp;
        argi.push_back(tmp);
    }

    /*
    * 가장 긴 증가하는 부분 수열 문제.
    * 백트래킹을 필요 없으니, 수열의 크기만 출력하면 된다.
    */
    for (const int& i : argi) {
        if (res.empty() || i > res.back()) {
            res.push_back(i);
        }
        else if (i < res.front()) {
            res[0] = i;
        }
        else {
            *upper_bound(res.begin(), res.end(), i - 1) = i;
        }
    }

    cout << res.size();

    return 0;
}