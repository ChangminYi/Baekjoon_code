#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct dir {
    int row, col;
    dir(const int _r, const int _c) : row(_r), col(_c) {}
    dir operator+(const dir& other) { return dir(row + other.row, col + other.col); }
};

const vector<dir> poss_dir = {
    dir(1, 0), dir(0, 1), dir(-1, 0), dir(0, -1)
};

int n, m, cnt = 1;
vector<dir> graph[101][101];
bool visit[101][101], light_on[101][101];
queue<dir> que;

bool in_range(const dir& d) {
    return 1 <= d.row && d.row <= n && 1 <= d.col && d.col <= n;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * �濡 �����Ϸ��� �õ��� �ߴٴ� ���� visit�� �����ϰ�, ���� ���� �ִ� ���� light_on�� ����.
    * ���� ���� ��忡�� ���� Ų ���� ���� �õ��� ������ �ߴٸ� ī��Ʈ �ø��� ť�� �� ��� ����.
    * ���� ����� ���� ��忡 ��� ���� �õ��� �ϰ�, ���� ���� �ִٸ� ť�� �� ��� ����.
    */

    cin >> n >> m;
    for (int x, y, a, b; m; m--) {
        cin >> x >> y >> a >> b;
        graph[x][y].push_back(dir(a, b));
    }

    light_on[1][1] = true;
    visit[1][1] = true;
    que.push(dir(1, 1));
    while (!que.empty()) {
        dir cur = que.front();
        que.pop();

        for (const dir& nxt : graph[cur.row][cur.col]) {
            if (!light_on[nxt.row][nxt.col]) {
                cnt++;
                light_on[nxt.row][nxt.col] = true;
                if (visit[nxt.row][nxt.col]) {
                    que.push(nxt);
                }
            }
        }

        for (const dir& pd : poss_dir) {
            dir adj = cur + pd;
            if (in_range(adj) && !visit[adj.row][adj.col]) {
                visit[adj.row][adj.col] = true;
                if (light_on[adj.row][adj.col]) {
                    que.push(adj);
                }
            }
        }
    }

    cout << cnt;

    return 0;
}