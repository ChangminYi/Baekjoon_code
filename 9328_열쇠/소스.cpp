#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <cctype>

#define MAX 102
using namespace std;

typedef pair<int, int> pint;

const char ALPHA_SIZE = 26;
const char EMPTY = '.';
const char PAPER = '$';
const char WALL = '*';
const vector<pint> poss_dir{
    make_pair(0, 1),
    make_pair(0, -1),
    make_pair(1, 0),
    make_pair(-1, 0)
};

int h, w;
vector<vector<char>> board(MAX, vector<char>(MAX));
vector<vector<bool>> visit(MAX, vector<bool>(MAX));
vector<bool> avail_key = vector<bool>(ALPHA_SIZE);
string init_key;

pint operator+(const pint& a, const pint& b) {
    return make_pair(a.first + b.first, a.second + b.second);
}

bool in_range(const pint& p) {
    return (0 <= p.first && p.first <= h + 1 && 0 <= p.second && p.second <= w + 1);
}

bool is_paper(const pint& p) {
    return (board[p.first][p.second] == PAPER);
}

bool is_wall(const pint& p) {
    return (board[p.first][p.second] == WALL);
}

bool is_door(const pint& p) {
    return isupper(board[p.first][p.second]);
}

bool is_key(const pint& p) {
    return islower(board[p.first][p.second]);
}

int get_index(const pint& p) {
    char dat = board[p.first][p.second];
    return (isupper(dat) ? dat - 'A' : dat - 'a');
}

int get_max_count(pint start) {
    int cnt = 0;
    queue<pint> que;
    vector<queue<pint>> door(ALPHA_SIZE);
    
    que.push(start);
    visit[start.first][start.second] = true;
    while (!que.empty()) {
        pint cur = que.front();
        que.pop();

        for (const pint& dir : poss_dir) {
            pint nxt = cur + dir;

            if (in_range(nxt) && !is_wall(nxt) && !visit[nxt.first][nxt.second]) {
                visit[nxt.first][nxt.second] = true;

                if (is_door(nxt)) {
                    if (avail_key[get_index(nxt)]) {
                        que.push(nxt);
                    }
                    else {
                        door[get_index(nxt)].push(nxt);
                    }
                }
                else {
                    if (is_key(nxt)) {
                        int idx = get_index(nxt);
                        if (!avail_key[idx]) {
                            avail_key[idx] = true;

                            while (!door[idx].empty()) {
                                que.push(door[idx].front());
                                door[idx].pop();
                            }
                        }
                    }
                    else if (is_paper(nxt)) {
                        cnt++;
                    }

                    que.push(nxt);
                }
            }
        }
    }

    return cnt;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    int iter;
    cin >> iter;

    do{
        cin >> h >> w;

        for (int i = 0; i < h + 2; i++) {
            fill(board[i].begin(), board[i].begin() + w + 2, EMPTY);
            fill(visit[i].begin(), visit[i].begin() + w + 2, false);
        }
        for (int i = 1; i <= h; i++) {
            for (int j = 1; j <= w; j++) {
                cin >> board[i][j];
            }
        }

        fill(avail_key.begin(), avail_key.end(), false);
        cin >> init_key;
        if (init_key != "0") {
            for (char& c : init_key) {
                avail_key[c - 'a'] = true;
            }
        }

        cout << get_max_count(make_pair(0, 0)) << '\n';

    } while (--iter > 0);

    return 0;
}