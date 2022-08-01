#include <iostream>
#include <cmath>

using namespace std;

const int INF = INT32_MAX / 2;
const int NOT_VISIT = -1;

int n, p, init_bit = 0;
int cost[16][16];
int dp[1 << 16];
char is_running[16];

int get_visit_cnt(int visit_bit) {
    int ret = 0;
    for(; visit_bit; visit_bit >>= 1) {
        if(visit_bit & 1) ret++;
    }
    return ret;
}

int dfs(const int visit_bit) {
    if(get_visit_cnt(visit_bit) >= p)
        return 0;
    else if(dp[visit_bit] != NOT_VISIT)
        return dp[visit_bit];
    else {
        dp[visit_bit] = INF;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if((visit_bit & (1 << i)) != 0 && (visit_bit & (1 << j)) == 0)
                    dp[visit_bit] = min(dp[visit_bit], dfs(visit_bit | (1 << j)) + cost[i][j]);
            }
        }
        return dp[visit_bit];
    }
}

int main() {
    /**
     * dfs를 통해 상태를 탐색하지만, dp를 사용하여 시간을 단축한다.
     * 발전소의 가동 상태를 비트마스킹을 통해 표현한다.
     * 가동 중인 발전소의 수가 p개 이상이면 더 이상 탐색할 필요가 없다.
     * 특정 가동 상태에서, 가동 중인 발전소로 가동 중이 아닌 발전소를 고치는
     * 조합의 비용의 최솟값을 dp 배열에 저장한다. 최초 가동 상태의 dp 값이 정답이 된다.
     */

	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);
    
    cin >> n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> cost[i][j];
        }
    }
    for(int i = 0; i < n; i++) {
        cin >> is_running[i];
        if(is_running[i] == 'Y') init_bit |= (1 << i);
    }
    cin >> p;

    fill(dp, dp + (1 << n), NOT_VISIT);
    int ans = dfs(init_bit);

    cout << (ans == INF ? -1 : ans);

	return 0;
}