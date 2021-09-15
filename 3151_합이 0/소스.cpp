#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long lli;

int n;
vector<int> argi;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    argi.resize(n);
    for (int& i : argi) {
        cin >> i;
    }
    sort(argi.begin(), argi.end());

    /*
    * i와 j를 고정하면, -(argi[i] + argi[j])를
    * (j+1, n]의 구간에서 찾으면 된다.
    * 하지만 그 값이 여러 개가 있을 수 있으므로,
    * upper_bound와 lower_bound를 사용하여 중복 개수를 찾아
    * 전체 카운트에 더해준다.
    */
    lli cnt = 0;
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            int tmp_sum = argi[i] + argi[j];

            auto lb = lower_bound(argi.begin() + j + 1, argi.end(), -tmp_sum);
            auto ub = upper_bound(argi.begin() + j + 1, argi.end(), -tmp_sum);

            cnt += distance(lb, ub);
        }
    }

    cout << cnt;

    return 0;
}