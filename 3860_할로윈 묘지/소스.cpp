#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct dir {
    int row, col;
    dir(const int _r = 0, const int _c = 0) : row(_r), col(_c) {}
    dir operator+(const dir& other) {
        return dir(this->row + other.row, this->col + other.col);
    }
};

struct edge {
    dir node;
    int dist;
    edge(const dir _n = dir(), const int _d = 0) : node(_n), dist(_d) {}
};
typedef edge qn;

const int INF = INT32_MAX / 2;
const vector<dir> poss_dir = {
    dir(1, 0), dir(-1, 0), dir(0, 1), dir(0 , -1)
};

int w, h, g, e;
bool board[30][30], visit[30][30], in_queue[30][30];
int dist[30][30], cycle[30][30];
vector<edge> graph[30][30];

bool in_range(const dir& d) {
    return 0 <= d.row && d.row < h && 0 <= d.col && d.col < w;
}

void clear_var() {
    for (int i = 0; i < h; i++) {
        fill(board[i], board[i] + w, true);
        fill(visit[i], visit[i] + w, false);
        fill(in_queue[i], in_queue[i] + w, false);
        fill(cycle[i], cycle[i] + w, 0);
        fill(dist[i], dist[i] + w, INF);
        for (int j = 0; j < w; j++) {
            graph[i][j].clear();
        }
    }
}

bool spfa() {
    queue<dir> que;

    dist[0][0] = 0;
    in_queue[0][0] = true;
    visit[0][0] = true;
    que.push(dir(0, 0));
    while (!que.empty()) {
        dir cur = que.front();
        in_queue[cur.row][cur.col] = false;
        que.pop();

        if (cur.row == h - 1 && cur.col == w - 1) {
            continue;
        }
        else {
            if (graph[cur.row][cur.col].empty()) {
                for (const dir& pd : poss_dir) {
                    dir nxt = cur + pd;
                    int new_dist = dist[cur.row][cur.col] + 1;
                    if (in_range(nxt) && board[nxt.row][nxt.col] && new_dist < dist[nxt.row][nxt.col]) {
                        visit[nxt.row][nxt.col] = true;
                        dist[nxt.row][nxt.col] = new_dist;
                        if (!in_queue[nxt.row][nxt.col]) {
                            if (++cycle[nxt.row][nxt.col] < w * h) {
                                in_queue[nxt.row][nxt.col] = true;
                                que.push(nxt);
                            }
                            else {
                                return true;
                            }
                        }
                    }
                }
            }
            else {
                for (const edge& e : graph[cur.row][cur.col]) {
                    const dir& nxt = e.node;
                    int new_dist = dist[cur.row][cur.col] + e.dist;
                    if (new_dist < dist[nxt.row][nxt.col]) {
                        visit[nxt.row][nxt.col] = true;
                        dist[nxt.row][nxt.col] = new_dist;
                        if (!in_queue[nxt.row][nxt.col]) {
                            if (++cycle[nxt.row][nxt.col] < w * h) {
                                in_queue[nxt.row][nxt.col] = true;
                                que.push(nxt);
                            }
                            else {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}

int main() {
    /*
    * ���� ����ġ�� ������ ���ԵǹǷ� ����-����, Ȥ�� spfa �˰����� ����Ͽ� �ִܰŸ��� ���Ѵ�.
    * �� �ڵ忡���� spfa �˰����� ����Ͽ���. (0, 0)���� ����Ͽ��� �� ����Ŭ�� �ִ� ����
    * ���� �켱������ �ǴܵǾ�� �Ѵ�. ���� �ִٸ� Never�� ����Ѵ�. �� ������ �������� (h-1, w-1)��
    * ������ �� �ִ����� �Ǻ��Ѵ�. �ִܰŸ� ���� �������� �湮�� ��� ��带 üũ�Ͽ� Ȯ���� �� �ִ�.
    * �湮�ߴٸ� �Ÿ��� ����ϰ�, �ƴ϶�� Impossible�� ����Ѵ�.
    * Ž�� ��, �ͽ� ������ �ִ� ĭ�� �ݵ�� �ͽ� ���۸��� �̿��ؾ� �Ѵ�.
    * ������ ��忡���� ��� Ž���� �������� �ʾƾ� �Ѵ�.
    */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    while (true) {
        cin >> w >> h;
        if (w == 0 && h == 0) break;
        clear_var();
        cin >> g;
        for (int x, y; g > 0; g--) {
            cin >> x >> y;
            board[y][x] = false;
        }
        cin >> e;
        for (int x1, y1, x2, y2, t; e > 0; e--) {
            cin >> x1 >> y1 >> x2 >> y2 >> t;
            graph[y1][x1].push_back(edge(dir(y2, x2), t));
        }

        if (spfa()) {
            cout << "Never\n";
        }
        else {
            if (visit[h - 1][w - 1]) {
                cout << dist[h - 1][w - 1] << '\n';
            }
            else {
                cout << "Impossible\n";
            }
        }
    }

    return 0;
}
