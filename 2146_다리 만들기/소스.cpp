#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

typedef pair<int, int> pint;

struct node {
    int mov = 0;
    pint cur = pint(0, 0);
    node(int m, pint c) : mov(m), cur(c) {}
};

const vector<pint> poss_dir = {
    pint(0, 1), pint(0, -1),
    pint(1, 0), pint(-1, 0)
};

int n;
vector<vector<bool>> board, visit;
vector<pint> root;
vector<vector<pint>> parent;

pint operator+(const pint& lhs, const pint& rhs) {
    return pint(lhs.first + rhs.first, lhs.second + rhs.second);
}

bool in_range(const pint& p) {
    return ((0 <= p.first && p.first < n) && (0 <= p.second && p.second < n));
}

pint find_parent(const pint& p) {
    if (parent[p.first][p.second] == p) {
        return p;
    }
    else {
        return parent[p.first][p.second] = find_parent(parent[p.first][p.second]);
    }
}

void union_elem(const pint& x, const pint& y) {
    pint f_x = find_parent(x), f_y = find_parent(y);
    if (f_x > f_y) {
        swap(f_x, f_y);
    }
    parent[f_y.first][f_y.second] = f_x;
}

void init_parent(const pint& start) {
    queue<pint> q;
    q.push(start);

    while (!q.empty()) {
        pint cur = q.front();
        q.pop();

        for (const pint& dir : poss_dir) {
            pint nxt = cur + dir;

            if (in_range(nxt) && board[nxt.first][nxt.second] && find_parent(cur) != find_parent(nxt)) {
                union_elem(cur, nxt);
                q.push(nxt);
            }
        }
    }
}

int get_min_dist(pint start) {
    for (vector<bool>& row : visit) {
        fill(row.begin(), row.end(), false);
    }

    queue<pint> par_que;
    queue<node> que;
    par_que.push(start);
    visit[start.first][start.second] = true;
    /*
    * ����� Ž���ϸ鼭 �ٴٿ� �����ߴٸ� ť�� �߰��ϰ�,
    * ���� ���̶�� ��� Ž�� ����
    */
    while (!par_que.empty()) {
        pint cur = par_que.front();
        par_que.pop();

        for (const pint& dir : poss_dir) {
            pint nxt = cur + dir;

            if (in_range(nxt) && !visit[nxt.first][nxt.second]) {
                visit[nxt.first][nxt.second] = true;

                if (board[nxt.first][nxt.second]) {
                    par_que.push(nxt);
                }
                else {
                    que.push(node(1, nxt));
                }
            }
        }
    }

    /*
    * ���� ���� �ٸ� ������ ���� ������ ��찡 �ּҰŸ�, �ٷ� �Ÿ� ��ȯ
    * ��� �ٴ��̸� Ž�� ����, ���� �����̸� ����
    */
    while (!que.empty()) {
        pint cur = que.front().cur;
        int cur_mov = que.front().mov;
        que.pop();

        for (const pint& dir : poss_dir) {
            pint nxt = cur + dir;

            if (in_range(nxt)) {
                if (board[nxt.first][nxt.second] && start != find_parent(nxt)) {
                    return cur_mov;
                }
                else if (!board[nxt.first][nxt.second] && !visit[nxt.first][nxt.second]) {
                    visit[nxt.first][nxt.second] = true;
                    que.push(node(cur_mov + 1, nxt));
                }
            }
        }
    }

    return INT32_MAX;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    board.resize(n, vector<bool>(n));
    visit.resize(n, vector<bool>(n));
    parent.resize(n, vector<pint>(n));

    for (int i = 0, tmp; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> tmp;
            board[i][j] = (tmp == 1);
            parent[i][j] = pint(i, j);
        }
    }

    // ��������� ���� ���� �� find_union ����
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            pint cur = pint(i, j);

            if (board[i][j] && find_parent(cur) == cur) {
                init_parent(cur);
                root.push_back(cur);
            }
        }
    }

    // �� ��������� �ּ��� ���� ã��
    int bridge_len = INT32_MAX;
    for (const pint& s : root) {
        bridge_len = min(bridge_len, get_min_dist(s));
    }

    cout << bridge_len;

    return 0;
}