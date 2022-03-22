#include <iostream>
#include <cmath>

using namespace std;

const double NOT_VISIT = -1.0;

int n, all_visit;
double arg[16][2], dist[16][16], dp[16][1 << 16];

inline double get_dist(const int i, const int j) {
    double x_diff = arg[i][0] - arg[j][0];
    double y_diff = arg[i][1] - arg[j][1];
    return sqrt(x_diff * x_diff + y_diff * y_diff);
}

double travel(const int cur, const int visit_bit) {
    if (visit_bit == all_visit) {
        return dist[cur][0];
    }
    else {
        double& ret = dp[cur][visit_bit];
        if (ret == NOT_VISIT) {
            ret = INT32_MAX;
            for (int i = 1; i < n; i++) {
                if ((visit_bit & (1 << i)) == 0) {
                    ret = min(ret, travel(i, visit_bit | (1 << i)) + dist[cur][i]);
                }
            }
        }
        return ret;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * dfs를 수행하면서, 현재까지 방문했던 모든 노드를 비트로 저장한다.
    * 이미 방문한 곳은 dp 배열에 저장하여 탐색 속도를 높인다.
    * 0번 노드에서 출발한 후, 0번으로 다시 돌아올 때까지의 거리의 최솟값을 구하면 된다.
    */

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arg[i][0] >> arg[i][1];
        fill(dp[i], dp[i] + (1 << n), NOT_VISIT);
    }

    all_visit = (1 << n) - 1;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            dist[i][j] = dist[j][i] = get_dist(i, j);
        }
    }

    cout << fixed << travel(0, 1 << 0);

    return 0;
}