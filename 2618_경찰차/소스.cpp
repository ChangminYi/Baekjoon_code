#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> pint;

const int MAX = 1001;
const int NOT_VISIT = -1;

int n, w;
vector<vector<int>> dp(MAX, vector<int>(MAX, NOT_VISIT));
vector<pint> to_go(MAX);

// 두 점 간 거리 계산
int calc_dist(const pint& a, const pint& b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int get_dist(int p1, int p2) {
    if (p1 == w || p2 == w) {
        return 0;
    }
    else {
        if (dp[p1][p2] == NOT_VISIT) {
            int nxt_idx = max(p1, p2) + 1;
            /*
            * 각각의 경찰차에 대해서 사건까지의 거리 계산 후,
            * 다음 dp값을 구하여 더함
            * 그 중 더 작은 값이 현재 dp값이 된다
            */
            int dist1 = calc_dist((p1 == 0 ? pint(1, 1) : to_go[p1]), to_go[nxt_idx]);
            int dist2 = calc_dist((p2 == 0 ? pint(n, n) : to_go[p2]), to_go[nxt_idx]);
            dist1 += get_dist(nxt_idx, p2);
            dist2 += get_dist(p1, nxt_idx);

            dp[p1][p2] = min(dist1, dist2);
        }

        return dp[p1][p2];
    }
}

void print_route(int p1, int p2) {
    if (p1 == w || p2 == w) {
        return;
    }
    else {
        int nxt_idx = max(p1, p2) + 1;
        int dist1 = calc_dist((p1 == 0 ? pint(1, 1) : to_go[p1]), to_go[nxt_idx]);
        int dist2 = calc_dist((p2 == 0 ? pint(n, n) : to_go[p2]), to_go[nxt_idx]);

        if (dist1 + dp[nxt_idx][p2] < dist2 + dp[p1][nxt_idx]) {
            cout << 1 << '\n';
            print_route(nxt_idx, p2);
        }
        else {
            cout << 2 << '\n';
            print_route(p1, nxt_idx);
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> w;
    for (int i = 1; i <= w; i++) {
        cin >> to_go[i].first >> to_go[i].second;
    }

    cout << get_dist(0, 0) << '\n';
    print_route(0, 0);

    return 0;
}