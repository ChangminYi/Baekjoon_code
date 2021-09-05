#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pint;
struct node {
	pint pos = make_pair(0, 0);
	int key_possessing = 0;
	int move_count = 0;
	node(const pint& p, const int kp, const int mc) :pos(p), key_possessing(kp), move_count(mc) {}
};

const char EMPTY = '.';
const char WALL = '#';
const char INIT_POS = '0';
const char FINISHING = '1';
const int MAX_DEPTH = (1 << 6);	// 가능한 열쇠 소유의 가짓수
const vector<pint> poss_dir = {
	make_pair(0, 1),
	make_pair(0, -1),
	make_pair(1, 0),
	make_pair(-1, 0)
};

int n, m;
pint start_point;
vector<vector<char>> board;
vector<vector<vector<bool>>> visit; // 열쇠 소지 상황에 따른 모든 visit 배열
queue<node> que;

bool in_range(const pint& p) {
	return ((0 <= p.first && p.first < n) && (0 <= p.second && p.second < m));
}

pint operator+(const pint& lhs, const pint& rhs) {
	return make_pair(lhs.first + rhs.first, lhs.second + rhs.second);
}

bool is_key(const pint& p) {
	return 'a' <= board[p.first][p.second] && board[p.first][p.second] <= 'f';
}

bool is_door(const pint& p) {
	return 'A' <= board[p.first][p.second] && board[p.first][p.second] <= 'F';
}

bool has_key(const pint& p, int key_list) {
	return ((1 << (board[p.first][p.second] - 'A')) & key_list) != 0;
}

int bfs() {
	int ret = -1;

	visit[start_point.first][start_point.second][0] = true;
	que.push(node(start_point, 0, 0));
	while (!que.empty()) {
		node cur = que.front();
		que.pop();

		if (board[cur.pos.first][cur.pos.second] == FINISHING) {
			ret = cur.move_count;
			break;
		}
		else {
			for (const pint& dir : poss_dir) {
				pint nxt = cur.pos + dir;

				if (in_range(nxt) &&
					board[nxt.first][nxt.second] != WALL &&
					!visit[nxt.first][nxt.second][cur.key_possessing]) {
					if (is_key(nxt)) {
						int new_key_set = cur.key_possessing | (1 << (board[nxt.first][nxt.second] - 'a'));
						
						visit[nxt.first][nxt.second][new_key_set] = true;
						que.push(node(nxt, new_key_set, cur.move_count + 1));
					}
					else if (is_door(nxt)) {
						/*
						* 문을 딸 수 있다면 따고 넘어간다.
						* 없다면 아무것도 할 수 없다.
						*/
						if (has_key(nxt, cur.key_possessing)) {
							visit[nxt.first][nxt.second][cur.key_possessing] = true;
							que.push(node(nxt, cur.key_possessing, cur.move_count + 1));
						}
						else {
							continue;
						}
					}
					else {
						visit[nxt.first][nxt.second][cur.key_possessing] = true;
						que.push(node(nxt, cur.key_possessing, cur.move_count + 1));
					}
				}
			}
		}
	}

	return ret;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> m;
	board.resize(n, vector<char>(m));
	visit.resize(n, vector<vector<bool>>(m, vector<bool>(MAX_DEPTH, false)));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> board[i][j];

			if (board[i][j] == INIT_POS) {
				board[i][j] = EMPTY;
				start_point = make_pair(i, j);
			}
		}
	}

	cout << bfs();

	return 0;
}