#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>

using namespace std;

typedef long long lli;
typedef pair<lli, lli> plli;

int n;
vector<plli> arg;

double get_dist(const plli &lhs, const plli& rhs) {
    lli x_diff = lhs.first - rhs.first;
    lli y_diff = lhs.second - rhs.second;

    return sqrt(x_diff * x_diff + y_diff * y_diff);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    arg.resize(n);
    for (plli& p : arg) {
        cin >> p.first >> p.second;
    }

    /*
    * 어느 한 점에서 다른 점으로의 거리의 최댓값의 최솟값 구하기.
    * 출력은 어느 점이든 상관 없으므로 편의상 입력에 주어진 점으로 한다.
    */
    double max_dist = (double)INT64_MAX;
    plli ans;
    for (int i = 0; i < n; i++) {
        double tmp_dist = 0;
        
        for (int j = 0; j < n; j++) {
            if (i != j) {
                tmp_dist = max(tmp_dist, get_dist(arg[i], arg[j]));
            }
        }

        if (tmp_dist < max_dist) {
            max_dist = tmp_dist;
            ans = arg[i];
        }
    }

    cout << ans.first << ' ' << ans.second;

    return 0;
}