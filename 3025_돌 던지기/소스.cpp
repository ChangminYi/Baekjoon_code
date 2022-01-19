#include <iostream>
#include <vector>
#include <stack>
#include <set>

using namespace std;

typedef pair<int, int> pint;

const char EMPTY = '.';
const char WALL = 'X';
const char STONE = 'O';

int r, c, n;
char board[30002][32];
stack<pint> cache[32];
set<int> not_empty[32];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 행이 30000까지이기 때문에, 단순하게 돌을 한 칸씩 옮기면 시간 초과.
    * 돌이 놓인 가장 위쪽의 자리들을 저장하고, 각 열의 가장 위에서 돌이 떨어졌을 때
    * 마지막으로 굴러가는 위치를 저장하여, 돌의 이동을 건너뛰면서 자리를 정해줘야 한다.
    * 각 돌을 떨어뜨리기 전에, 굴러가는 위치가 유효한지 검사하고 최신화한다.
    */
    cin >> r >> c;
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            cin >> board[i][j];
            if (board[i][j] == WALL) {
                not_empty[j].insert(i);
            }
        }
    }
    for (int i = 1; i <= c; i++) {
        not_empty[i].insert(r + 1);
    }

    cin >> n;
    do {
        int start_col, row, col;
        cin>> start_col;

        while (!cache[start_col].empty()) {
            if (board[cache[start_col].top().first][cache[start_col].top().second] == EMPTY) {
                break;
            }
            else {
                cache[start_col].pop();
            }
        }
        row = cache[start_col].empty() ? 1 : cache[start_col].top().first;
        col = cache[start_col].empty() ? start_col : cache[start_col].top().second;
        
        /*
        * 옮겨갈 수 있는 위치 중, 가장 마지막으로 돌이 놓인 곳을 찾는다. 그 바로 윗칸에
        * 돌이 떨어져 내려오는데, 움직일 수 있으면 다시 떨어뜨리고, 조건이 맞지 않으면
        * 윗칸에 돌을 놓고 보드를 업데이트한다. 돌이 떨어지는 과정에서, 저장하지 않은
        * 새로운 떨어지는 칸이 있다면, 스택에 추가한다.
        */
        while (true) {
            row = *not_empty[col].upper_bound(row);
            if (board[row][col] == STONE) {
                if (board[row - 1][col - 1] == EMPTY && board[row][col - 1] == EMPTY) {
                    cache[start_col].push(pint(row - 1, col));
                    row--, col--;
                }
                else if (board[row - 1][col + 1] == EMPTY && board[row][col + 1] == EMPTY) {
                    cache[start_col].push(pint(row - 1, col));
                    row--, col++;
                }
                else {
                    board[row - 1][col] = STONE;
                    not_empty[col].erase(row);
                    not_empty[col].insert(row - 1);
                    break;
                }
            }
            else {
                board[row - 1][col] = STONE;
                not_empty[col].erase(row), not_empty[col].insert(row - 1);
                break;
            }
        }
    } while (--n);

    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            cout << board[i][j];
        }
        cout << '\n';
    }

    return 0;
}