#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

typedef pair<int, int> pint;

const vector<pint> poss_dir = {
    pint(0, 1), pint(0, -1),
    pint(1, 0), pint(-1, 0)
};

int n;
vector<vector<bool>> board, visit;
queue<pint> que;
priority_queue<int, vector<int>, greater<int>> pq;

pint operator+(const pint& lhs, const pint& rhs) {
    return pint(lhs.first + rhs.first, lhs.second + rhs.second);
}

bool in_range(const pint& p) {
    return (0 <= p.first && p.first < n) && (0 <= p.second && p.second < n);
}

int bfs(pint start) {
    int cnt = 1;

    visit[start.first][start.second] = true;
    que.push(start);
    while (!que.empty()) {
        pint cur = que.front();
        que.pop();

        for (const pint& dir : poss_dir) {
            pint nxt = cur + dir;

            if (in_range(nxt) && board[nxt.first][nxt.second] && !visit[nxt.first][nxt.second]) {
                cnt++;
                visit[nxt.first][nxt.second] = true;
                que.push(nxt);
            }
        }
    }

    return cnt;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;

    board.resize(n, vector<bool>(n));
    visit.resize(n, vector<bool>(n, false));

    char tmp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> tmp;

            board[i][j] = (tmp == '1');
        }
    }

    /*
    * ���� �湮���� ���� ���� ������ ������, bfs ����
    * bfs�� �����Ͽ� ���� ������ ũ�⸦ �켱���� ť�� ����
    * �� �� ���Ŀ� �°� ���.
    */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] && !visit[i][j]) {
                pq.push(bfs(pint(i, j)));
            }
        }
    }

    cout << pq.size() << '\n';
    for (; !pq.empty(); pq.pop()) {
        cout << pq.top() << '\n';
    }

    return 0;

}