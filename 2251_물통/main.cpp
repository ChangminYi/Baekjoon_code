#include <iostream>
#include <cmath>
#include <set>
#include <array>

using namespace std;

const int NOT_VISIT = -1;

array<int, 3> max_vol;
int visit[201][201];

void dfs(array<int, 3> cur) {
    array<int, 3> nxt;
    int diff;
    
    for(int i = 0; i < 3; i++) {    // i to j
        for(int j = 0; j < 3; j++) {
            if(i == j) continue;
            nxt[0] = cur[0], nxt[1] = cur[1], nxt[2] = cur[2];
            diff = min(max_vol[j] - cur[j], cur[i]);
            nxt[i] -= diff, nxt[j] += diff;
            if(visit[nxt[0]][nxt[1]] == NOT_VISIT) {
                visit[nxt[0]][nxt[1]] = nxt[2];
                dfs(nxt);
            }
        }
    }
}

int main() {
    /**
     * a, b, c 세 물통에서 각각을 이동시킬 때,
     * 두 물통에서 넣거나 뺄 수 있는 값 중 작은 값을 이동시킨다.
     * dfs로 탐색하면서 visit에는 (a, b) 쌍에 대한 c의 값을 저장한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);
    
    cin >> max_vol[0] >> max_vol[1] >> max_vol[2];
    for(int i = 0; i <= 200; i++)
        fill(visit[i], visit[i] + 201, NOT_VISIT);

    visit[0][0] = max_vol[2];
    dfs({ 0, 0, max_vol[2] });

    set<int> ans;
    for(int i = 0; i <= max_vol[1]; i++) {
        if(visit[0][i] != NOT_VISIT)
            ans.insert(visit[0][i]);
    }

    for(const int& i: ans) {
        cout << i << ' ';
    }

    return 0;
}