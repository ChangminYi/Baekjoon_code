#include <iostream>
#include <cmath>

using namespace std;

int n, lo, hi, x;
int arg[15];
bool visit[15];

int dfs(const int depth) {
    if(depth == n) {
        int min_val = INT32_MAX, max_val = 0, sum = 0;
        for(int i = 0; i < n; i++) {
            if(!visit[i]) continue;

            min_val = min(min_val, arg[i]), max_val = max(max_val, arg[i]);
            sum += arg[i];
        }

        if(lo <= sum && sum <= hi && max_val - min_val >= x) return 1;
        else return 0;
    }
    else {
        int ret = 0;
        visit[depth] = true;
        ret += dfs(depth + 1);
        visit[depth] = false;
        ret += dfs(depth + 1);
        return ret;
    }
}

int main() {
    /**
     * n이 최대 15이므로, 모든 경우의 수를 다 탐색해봐도 무방하다.
     * algorithm 헤더의 permutation을 사용해도 되지만, dfs로 구현하였다.
     * 깊이가 n이 되었을 때, 선택한 노드들의 최솟값, 최댓값, 총합을 구하여
     * 조건을 만족한다면 1을 반환하고, 아니면 0을 반환한다.
     * n 미만의 깊이에서는 해당 깊이를 선택한 때와 하지 않았을 때의 경우의 수의 합을 구한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> lo >> hi >> x;
    for(int i = 0; i < n; i++) {
        cin >> arg[i];
    }

    cout << dfs(0);

    return 0;
}