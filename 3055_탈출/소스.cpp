#include <iostream>
#include <string>
#include <queue>

using namespace std;

struct dir {
    int x, y;
    dir(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};

const dir poss_dir[4] = {
    dir(0, 1), dir(0, -1), dir(1, 0), dir(-1, 0)
};

int r, c;
int min_flood[50][50];
char board[50][50];
bool visit[50][50];
dir stt, dst;
queue<pair<dir, int>> que;

bool in_range(const dir& p) {
    return 0 <= p.x && p.x < r && 0 <= p.y && p.y < c;
}

void init_min_flood() {
    while (!que.empty()) {
        dir cur = que.front().first;
        int cur_cnt = que.front().second;
        que.pop();

        for (int i = 0; i < 4; i++) {
            dir nxt = dir(cur.x + poss_dir[i].x, cur.y + poss_dir[i].y);
            if (in_range(nxt) && board[nxt.x][nxt.y] == '.' && cur_cnt + 1 < min_flood[nxt.x][nxt.y]) {
                min_flood[nxt.x][nxt.y] = cur_cnt + 1;
                que.push(make_pair(nxt, cur_cnt + 1));
            }
        }
    }
}

string bfs() {
    visit[stt.x][stt.y] = true;
    que.push(make_pair(stt, 0));
    while (!que.empty()) {
        dir cur = que.front().first;
        int cur_cnt = que.front().second;
        que.pop();

        if (cur.x == dst.x && cur.y == dst.y) {
            return to_string(cur_cnt);
        }
        else {
            for (int i = 0; i < 4; i++) {
                dir nxt = dir(cur.x + poss_dir[i].x, cur.y + poss_dir[i].y);
                if (in_range(nxt) && board[nxt.x][nxt.y] != 'X' && !visit[nxt.x][nxt.y]) {
                    if (cur_cnt + 1 < min_flood[nxt.x][nxt.y]) {
                        visit[nxt.x][nxt.y] = true;
                        que.push(make_pair(nxt, cur_cnt + 1));
                    }
                }
            }
        }
    }

    return "KAKTUS";
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * ���� �ִ� �ð��� ���� �ʱ�ȭ�� ��, bfs�� �����Ѵ�.
    * ���� ������ ĭ�� �ð����� ���� �ִ� �ð��� ���ų� ũ�ٸ� �� �� ����.
    * �̸� Ž�� ���ǿ� �߰��Ͽ� ����� ����ϸ� �ȴ�.
    */
    cin >> r >> c;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> board[i][j];
            min_flood[i][j] = 100000;

            if (board[i][j] == 'S') {
                stt = dir(i, j);
            }
            else if (board[i][j] == 'D') {
                dst = dir(i, j);
            }
            else if (board[i][j] == '*') {
                min_flood[i][j] = 0;
                que.push(make_pair(dir(i, j), 0));
            }
        }
    }

    init_min_flood();
    cout << bfs();

    return 0;
}