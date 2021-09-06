#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> pint;

const char EMPTY = '.';
const vector<pint> poss_dir = {
    make_pair(-1, 1),
    make_pair(0, 1),
    make_pair(1, 1)
};

int r, c, pipe_cnt;
vector<vector<char>> board;
vector<vector<bool>> visit;
bool ans_found;

pint operator+(const pint& lhs, const pint& rhs) {
    return make_pair(lhs.first + rhs.first, lhs.second + rhs.second);
}

bool in_range(const pint& p) {
    return (0 <= p.first && p.first < r) && (0 <= p.second && p.second < c);
}

/*
* dfs�� board�� ���� ������ Ž��
* ���� ������ �����ߴٸ� �������� ���� ���̹Ƿ� üũ�ϰ� ����
* ���� ������ ������ ���� �ʾҴٸ� ���̻� �� ��Ʈ�� ����� �� �����Ƿ�
* visit�� ǥ���ϰ� �ٸ� ��Ʈ Ž��
*/
void dfs(pint cur) {
    if (cur.second == c - 1) {
        ans_found = true;
        pipe_cnt++;
    }
    else {
        for (const pint& dir: poss_dir) {
            pint nxt = cur + dir;

            if (in_range(nxt) && board[nxt.first][nxt.second] == EMPTY && !visit[nxt.first][nxt.second]) {
                visit[nxt.first][nxt.second] = true;
                dfs(nxt);

                if (ans_found) {
                    return;
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> r >> c;
    board.resize(r, vector<char>(c));
    visit.resize(r, vector<bool>(c, false));
    for (vector<char>& row : board) {
        for (char& ch : row) {
            cin >> ch;
        }
    }

    for (int i = 0; i < r; i++) {
        ans_found = false;
        visit[i][0] = true;
        dfs(make_pair(i, 0));
    }

    cout << pipe_cnt;

    return 0;
}