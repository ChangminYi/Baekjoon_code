#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pint;

const char EMPTY = '.';
const char DIRTY = '*';
const char WALL = 'x';
const char START = 'o';

const vector<pint> poss_dir {
    pint(0, 1), pint(0, -1), pint(1, 0), pint(-1, 0)
};

int w, h;
pint init_dir;
char board[20][20];
bool visit[20][20];
int all_visit, dist[20][20][20][20];
vector<pint> dirty;

bool in_range(const pint& p) {
    return 0 <= p.first && p.first < h && 0 <= p.second && p.second < w;
}

bool init_dist(const pint start) {
    int ret = (int)dirty.size();
    queue<pint> que;
    for (int i = 0; i < h; i++) fill(visit[i], visit[i] + w, false);

    visit[start.first][start.second] = true;
    dist[start.first][start.second][start.first][start.second] = 0;
    que.push(start);
    while (!que.empty()) {
        pint cur = que.front();
        int& cur_dist = dist[start.first][start.second][cur.first][cur.second];
        que.pop();

        if (board[cur.first][cur.second] == DIRTY) ret--;
        for (const pint& pd : poss_dir) {
            pint nxt = pint(cur.first + pd.first, cur.second + pd.second);
            if (in_range(nxt) && !visit[nxt.first][nxt.second] && board[nxt.first][nxt.second] != WALL) {
                dist[start.first][start.second][nxt.first][nxt.second] = cur_dist + 1;
                visit[nxt.first][nxt.second] = true;
                que.push(nxt);
            }
        }
    }

    return ret == 0;
}

int get_min_dist(pint cur, int visit_bit, int total_dist) {
    if (visit_bit == all_visit) return total_dist;

    int min_dist = INT32_MAX;
    for (int i = 0, cur_dist; i < (int)dirty.size(); i++) {
        if ((visit_bit & (1 << i)) == 0) {
            cur_dist = dist[cur.first][cur.second][dirty[i].first][dirty[i].second];
            min_dist = min(min_dist, get_min_dist(dirty[i], visit_bit | (1 << i), total_dist + cur_dist));
        }
    }

    return min_dist;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 방의 모양을 입력받으면, 일단 시작 지점에서 모든 더러운 곳을 방문할 수 있는지를 검사한다.
    * 만약 한 군데라도 갈 수 없다면 모두 청소를 할 수 없으므로 -1을 출력한다.
    * 거리 탐색을 빠르게 하기 위해, 더러운 곳을 따로 저장하여 그 곳을 기준으로 거리를 미리
    * 계산하여 저장한다. 그리고 dfs와 비트마스킹을 통해 아직 방문하지 않은 더러운 곳을
    * 모두 방문해보고, 이동 횟수가 최소가 되는 값을 찾아 출력하면 된다.
    */

    while (true) {
        cin >> w >> h;
        if (w == 0 && h == 0) break;

        dirty.clear();
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                cin >> board[i][j];
                if (board[i][j] == START) {
                    board[i][j] = EMPTY;
                    init_dir = pint(i, j);
                }
                else if (board[i][j] == DIRTY) {
                    dirty.push_back(pint(i, j));
                }
            }
        }

        if (init_dist(init_dir)) {
            all_visit = (1 << dirty.size()) - 1;
            for (int i = 0; i < (int)dirty.size(); i++) {
                init_dist(dirty[i]);
            }

            int min_dist = INT32_MAX;
            for (int i = 0, start_dist; i < (int)dirty.size(); i++) {
                start_dist = dist[init_dir.first][init_dir.second][dirty[i].first][dirty[i].second];
                min_dist = min(min_dist, get_min_dist(dirty[i], 1 << i, start_dist));
            }

            cout << min_dist << '\n';
        }
        else{
            cout << "-1\n";
        }
    }

    return 0;
}