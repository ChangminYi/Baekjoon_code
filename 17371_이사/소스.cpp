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
    * ��� �� ������ �ٸ� �������� �Ÿ��� �ִ��� �ּڰ� ���ϱ�.
    * ����� ��� ���̵� ��� �����Ƿ� ���ǻ� �Է¿� �־��� ������ �Ѵ�.
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