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
    * ���� 30000�����̱� ������, �ܼ��ϰ� ���� �� ĭ�� �ű�� �ð� �ʰ�.
    * ���� ���� ���� ������ �ڸ����� �����ϰ�, �� ���� ���� ������ ���� �������� ��
    * ���������� �������� ��ġ�� �����Ͽ�, ���� �̵��� �ǳʶٸ鼭 �ڸ��� ������� �Ѵ�.
    * �� ���� ����߸��� ����, �������� ��ġ�� ��ȿ���� �˻��ϰ� �ֽ�ȭ�Ѵ�.
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
        * �Űܰ� �� �ִ� ��ġ ��, ���� ���������� ���� ���� ���� ã�´�. �� �ٷ� ��ĭ��
        * ���� ������ �������µ�, ������ �� ������ �ٽ� ����߸���, ������ ���� ������
        * ��ĭ�� ���� ���� ���带 ������Ʈ�Ѵ�. ���� �������� ��������, �������� ����
        * ���ο� �������� ĭ�� �ִٸ�, ���ÿ� �߰��Ѵ�.
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