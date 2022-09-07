#include <iostream>
#include <queue>

using namespace std;

struct qn {
    int a, b, c, cnt;
    qn(int _a, int _b, int _c, int _cnt) {
        a = _a, b = _b, c = _c, cnt = _cnt;
    }
};

const int minus_val[6][3] = {
    {1, 3, 9},
    {1, 9, 3},
    {3, 1, 9},
    {3, 9, 1},
    {9, 1, 3},
    {9, 3, 1}
};

int n, arg[3];
bool visit[61][61][61];
queue<qn> q;

int main() {
    /**
     * SCV는 반드시 3개가 있고, n이 3 미만이면 체력인 0인 SCV가 있는 것으로 모델링한다.
     * SCV의 최대 체력이 60이고, 최대 3개 있으므로 bfs를 통해 문제를 해결할 수 있다.
     * 6개의 가능한 공격 패턴을 적용하여 모든 SCV의 체력이 0이 될 때까지 탐색한다.
     * 만약 공격을 받은 SCV의 체력이 음수가 된다면 0으로 치환한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);    
    
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> arg[i];
    
    visit[arg[0]][arg[1]][arg[2]] = true;
    q.push(qn(arg[0], arg[1], arg[2], 0));
    while(!q.empty()) {
        int a = q.front().a, b = q.front().b, c = q.front().c;
        int cur_cnt = q.front().cnt;
        q.pop();

        if(a == 0 && b == 0 && c == 0) {
            cout << cur_cnt;
            break;
        }

        for(int i = 0, na, nb, nc; i < 6; i++) {
            na = max(0, a - minus_val[i][0]);
            nb = max(0, b - minus_val[i][1]);
            nc = max(0, c - minus_val[i][2]);

            if(!visit[na][nb][nc]) {
                visit[na][nb][nc] = true;
                q.push(qn(na, nb, nc, cur_cnt + 1));
            }
        }
    }

    return 0;
}