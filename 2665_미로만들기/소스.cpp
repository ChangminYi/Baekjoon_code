#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <functional>
#include <numeric>

using namespace std;

typedef pair<int, int> pint;
typedef pair<pint, int> edge;
typedef pair<int, pint> pqn;

const char BLACK = '0';
const int INF = INT32_MAX;
const vector<pint> poss_dir = {
    pint(1, 0), pint(-1, 0),
    pint(0, 1), pint(0, -1)
};

int n;
vector<string> board;
vector<edge> graph[50][50];
int dist[50][50];
priority_queue<pqn, vector<pqn>, greater<pqn>> pq;

const pint operator+(const pint& lhs, const pint& rhs) {
    return pint(lhs.first + rhs.first, lhs.second + rhs.second);
}

bool in_range(const pint& p) {
    return (0 <= p.first && p.first < n) && (0 <= p.second && p.second < n);
}

void dijk() {
    dist[0][0] = 0;
    pq.push(pqn(0, pint(0, 0)));
    while (!pq.empty()) {
        pint cur = pq.top().second;
        int cur_dist = pq.top().first;
        pq.pop();

        if (cur_dist <= dist[cur.first][cur.second]) {
            for (const edge& e : graph[cur.first][cur.second]) {
                pint nxt = e.first;
                int new_dist = cur_dist + e.second;

                if (new_dist < dist[nxt.first][nxt.second]) {
                    dist[nxt.first][nxt.second] = new_dist;
                    pq.push(pqn(new_dist, nxt));
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    board.resize(n);
    for (string& str : board) {
        cin >> str;
    }

    /*
    * 흰 방으로 바꾸어야 하는 검은 방의 수를 거리로 설정.
    * 만약 현재 방의 인접 방이 검은 방이라면, 거리는 1. 아니라면, 거리는 0.
    * 이를 바탕으로 시작점에서 도착점까지의 최단거리를 계산하면 된다.
    */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dist[i][j] = INF;
            pint cur = pint(i, j);

            for (const pint& dir : poss_dir) {
                pint adj = cur + dir;

                if (in_range(adj)) {
                    if (board[adj.first][adj.second] == BLACK) {
                        graph[i][j].push_back(edge(adj, 1));
                    }
                    else {
                        graph[i][j].push_back(edge(adj, 0));
                    }
                }
            }
        }
    }

    dijk();
    cout << dist[n - 1][n - 1];

    return 0;
}