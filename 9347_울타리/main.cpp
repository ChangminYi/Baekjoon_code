#include <iostream>
#include <vector>
#include <deque>

using namespace std;

struct dir {
    int row, col;
    dir(const int _r = 0, const int _c = 0) : row(_r), col(_c) {}
    dir operator+(const dir& other) const {
        return dir(row + other.row, col + other.col);
    }
};

const vector<dir> poss_dir = {
    dir(1, 0), dir(-1, 0), dir(0, 1), dir(0, -1)
};
const int NOT_VISIT = -1;

int t, r, c;
int board[1002][1002], dist[1002][1002];
deque<dir> deq;

bool in_range(const dir& d) {
    return 0 <= d.row && d.row < r && 0 <= d.col && d.col < c;
}

int main() {
    /**
     * 0-1 bfs를 통해 부숴야 하는 울타리의 수를 구할 수 있다.
     * 최대한 많이 울타리를 부쉈을 때, 얻을 수 있는 꽃의 수를 구해야 하므로
     * 거리가 최대이고 울타리가 아닌 점의 수를 모두 세면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> t;
    do {
        cin >> r >> c;
        for(int i = 1; i <= r; i++) {
            for(int j = 1; j <= c; j++) {
                cin >> board[i][j];
                dist[i][j] = NOT_VISIT;
            }
        }
        r += 2, c += 2;
        for(int i = 0; i < r; i++) {
            board[i][0] = board[i][c - 1] = 0;
            dist[i][0] = dist[i][c - 1] = NOT_VISIT;
        }
        for(int i = 0; i < c; i++) {
            board[0][i] = board[r - 1][i] = 0;
            dist[0][i] = dist[r - 1][i] = NOT_VISIT;
        }

        dist[0][0] = 0;
        deq.push_back(dir(0, 0));
        while(!deq.empty()) {
            dir cur = deq.front();
            deq.pop_front();

            for(const dir& pd: poss_dir) {
                dir nxt = cur + pd;
                if(!in_range(nxt) || dist[nxt.row][nxt.col] != NOT_VISIT) continue;
                
                dist[nxt.row][nxt.col] = dist[cur.row][cur.col] + board[nxt.row][nxt.col];
                (board[nxt.row][nxt.col] ? deq.push_back(nxt) : deq.push_front(nxt));
            }
        }

        r -= 2, c -= 2;
        int max_dist = -1, ans = 0;
        for(int i = 1; i <= r; i++) {
            for(int j = 1; j <= c; j++) {
                if(board[i][j]) continue;

                if(max_dist == dist[i][j]) ans++;
                else if(max_dist < dist[i][j]) {
                    max_dist = dist[i][j];
                    ans = 1;
                }
            }
        }

        cout << max_dist << ' ' << ans << '\n';
    } while(--t);

    return 0;
}