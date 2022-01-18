#include <iostream>
#include <queue>
#include <deque>
#include <numeric>
#include <algorithm>

using namespace std;

struct pos {
    int row, col;
    pos() : row(0), col(0) {}
    pos(int _r, int _c) : row(_r), col(_c) {}
};
istream& operator>>(istream& istr, pos& p) {
    return (istr >> p.row >> p.col);
}

const int NOT_VISIT = -1;
const int EMPTY = 0;
const int START = 0;
const int DEST = 1;
const deque<pos> poss_dir = {
    pos(0, 1), pos(0, -1),
    pos(1, 0), pos(-1, 0)
};

pos taxi;
int n, m, fuel;
int board[21][21], dist[21][21];
deque<pair<pos, pos>> dat;
queue<pos> que;

bool in_range(const pos& p) {
    return (1 <= p.row && p.row <= n) && (1 <= p.col && p.col <= n);
}

void update_dist() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist[i][j] = NOT_VISIT;
        }
    }

    dist[taxi.row][taxi.col] = 0;
    que.push(taxi);
    while (!que.empty()) {
        pos cur = que.front();
        que.pop();

        for (const pos& dir : poss_dir) {
            pos nxt(cur.row + dir.row, cur.col + dir.col);

            if (in_range(nxt) && board[nxt.row][nxt.col] == EMPTY && dist[nxt.row][nxt.col] == NOT_VISIT) {
                dist[nxt.row][nxt.col] = dist[cur.row][cur.col] + 1;
                que.push(nxt);
            }
        }
    }
}

bool comp(const pair<pos, pos>& lhs, const pair<pos, pos>& rhs) {
    const pos& l = lhs.first;
    const pos& r = rhs.first;
    if (dist[l.row][l.col] != dist[r.row][r.col]) {
        return dist[l.row][l.col] < dist[r.row][r.col];
    }
    else if (l.row != r.row) {
        return l.row < r.row;
    }
    else {
        return l.col < r.col;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * 현재 택시 위치에서 가장 가까운 승객 위치를 찾고, 그곳으로 이동.
    * 만약 연료가 부족하면 -1 출력하고 종료. 아니라면 승객 위치에서 목적지까지 이동.
    * 이 또한 연료 부족하면 -1 출력하고 종료. 이동에 성공했다면, 움직인 거리의 2배의
    * 연료를 받으므로, 현재 연료량에 승객승차-하차 거리만큼을 더해준다. 이를 반복하면 된다.
    */
    cin >> n >> m >> fuel;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> board[i][j];
        }
    }
    cin >> taxi;
    dat.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> dat[i].first >> dat[i].second;
    }
    
    while (!dat.empty()) {
        update_dist();
        sort(dat.begin(), dat.end(), comp);

        pos nxt_go = dat.front().first;
        pos nxt_dest = dat.front().second;
        dat.pop_front();

        if (dist[nxt_go.row][nxt_go.col] == NOT_VISIT || fuel < dist[nxt_go.row][nxt_go.col]) {
            cout << -1;
            return 0;
        }
        else {
            fuel -= dist[nxt_go.row][nxt_go.col];
            taxi = nxt_go;
            update_dist();

            if (dist[nxt_dest.row][nxt_dest.col] == NOT_VISIT || fuel < dist[nxt_dest.row][nxt_dest.col]) {
                cout << -1;
                return 0;
            }
            else {
                fuel += dist[nxt_dest.row][nxt_dest.col];
                taxi = nxt_dest;
            }
        }
    }

    cout << fuel;

    return 0;
}