#include<iostream>
#include<vector>
#include<queue>

using namespace std;

typedef pair<int, int> pint;
struct q_node {
    pint dir;
    int move;
    int time;
    int day;
    q_node(pint p = make_pair(0, 0), int m = 0, int t = 0, int d = 0) : dir(p), move(m), time(t), day(d) {}
};

const int WALL = 1;
const int EMPTY = 0;
const int SUN = 0;
const int MOON = 1;
const int MAX_DAYLIGHT = 2;
const int MAX_N = 500;
const int MAX_M = 11;
const vector<pint> poss_dir = {
    make_pair(0, 1),
    make_pair(0, -1),
    make_pair(1, 0),
    make_pair(-1, 0)
};

int n;
int daylight_switch;
vector<vector<int>> board;
bool visit[MAX_N][MAX_N][MAX_M][MAX_DAYLIGHT];

pint operator+ (const pint& a, const pint& b) {
    return make_pair(a.first + b.first, a.second + b.second);
}

void operator+=(pint& a, const pint& b) {
    a.first += b.first;
    a.second += b.second;
}

bool in_range(const pint& p) {
    if (0 <= p.first && p.first < n) {
        if (0 <= p.second && p.second < n) {
            return true;
        }
    }
    return false;
}

void bfs() {
    queue<q_node> que;

    que.push(q_node(make_pair(0, 0), 0, SUN, 1));
    visit[0][0][0][SUN] = true;
    
    while (!que.empty()) {
        pint cur = que.front().dir;
        int cur_move = que.front().move;
        int cur_time = que.front().time;
        int cur_day = que.front().day;
        que.pop();

        if (cur.first == n - 1 && cur.second == n - 1) {
            cout << cur_day << (cur_time == SUN ? " sun" : " moon");
            return;
        }
        else {
            int nxt_move = cur_move + 1;
            int nxt_day = cur_day;
            bool nxt_time = cur_time;
            if (nxt_move == daylight_switch) {
                nxt_move = 0;
                nxt_time = (cur_time == SUN ? MOON : SUN);

                if (nxt_time == SUN) {
                    nxt_day++;
                }
            }

            for (const pint& dir : poss_dir) {
                pint nxt = cur + dir;

                if (cur_time == MOON) {
                    while (in_range(nxt) && board[nxt.first][nxt.second] == WALL) {
                        nxt += dir;
                    }
                }

                if (in_range(nxt) && board[nxt.first][nxt.second] == EMPTY) {
                    if (!visit[nxt.first][nxt.second][nxt_move][nxt_time]) {
                        visit[nxt.first][nxt.second][nxt_move][nxt_time] = true;
                        que.push(q_node(nxt, nxt_move, nxt_time, nxt_day));
                    }
                }
            }
        }
    }

    cout << -1;
    return;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> daylight_switch;
    board = vector<vector<int>>(n, vector<int>(n));
    for (vector<int>& row : board) {
        for (int& i : row) {
            cin >> i;
        }
    }
    
    bfs();

    return 0;
}