#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int NOT_FOUND = -1;
const int DAY = 0;
const int NIGHT = 1;
const char EMPTY = '0';
const char WALL = '1';

typedef pair<int, int> pint;
typedef struct NODE {
	pint position;
	int daylight;
	int move_count;
	int wall_break;
	bool last_same;
	bool arrived(int x, int y) {
		return (this->position.first == x && this->position.second == y);
	}
	int get_next_day() {
		return (this->daylight == DAY ? NIGHT : DAY);
	}
	bool is_day() {
		return (this->daylight == DAY);
	}
	NODE() : position(make_pair(0, 0)), daylight(DAY), move_count(0), wall_break(0), last_same(false) {}
	NODE(pint _pos, int _day, int _mov_cnt, int _brck, bool _same) : position(_pos), daylight(_day), move_count(_mov_cnt), wall_break(_brck), last_same(_same) {}
}node;

vector<pint> dir = {
	{1, 0}, {0, 1}, {-1, 0}, {0, -1}
};

int n, m, k;
vector<vector<char>> board;
vector<vector<vector<bool>>> visit;
queue<node> que;

bool in_range(pint& p) {
	return (0 <= p.first && p.first < n && 0 <= p.second && p.second < m);
}

const pint operator+(const pint& a, const pint& b) {
	return make_pair(a.first + b.first, a.second + b.second);
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> n >> m >> k;
	board = vector<vector<char>>(n, vector<char>(m));
	visit = vector<vector<vector<bool>>>(n, vector<vector<bool>>(m, vector<bool>(k + 1, false)));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> board[i][j];
		}
	}

	int res = NOT_FOUND;
	que.push(node(make_pair(0, 0), DAY, 1, 0, false));
	visit[0][0][0] = true;
	while (!que.empty()) {
		node cur = que.front();
		que.pop();

		if (cur.arrived(n - 1, m - 1)) {
			res = cur.move_count;
			break;
		}
		else {
			if (cur.is_day()) {
				for (pint& p : dir) {
					pint nxt = cur.position + p;

					if (in_range(nxt)) {
						if (board[nxt.first][nxt.second] == EMPTY) {
							if (!visit[nxt.first][nxt.second][cur.wall_break]) {
								visit[nxt.first][nxt.second][cur.wall_break] = true;
								que.push(node(nxt, cur.get_next_day(), cur.move_count + 1, cur.wall_break, false));
							}
						}
						else {
							if (cur.wall_break < k && !visit[nxt.first][nxt.second][cur.wall_break + 1]) {
								visit[nxt.first][nxt.second][cur.wall_break + 1] = true;
								que.push(node(nxt, cur.get_next_day(), cur.move_count + 1, cur.wall_break + 1, false));
							}
						}
					}
				}
			}
			else {
				for (pint& p : dir) {
					pint nxt = cur.position + p;

					if (in_range(nxt)) {
						if (board[nxt.first][nxt.second] == EMPTY) {
							if (!visit[nxt.first][nxt.second][cur.wall_break]) {
								visit[nxt.first][nxt.second][cur.wall_break] = true;
								que.push(node(nxt, cur.get_next_day(), cur.move_count + 1, cur.wall_break, false));
							}
						}
						else {
							if (!cur.last_same && cur.wall_break < k && !visit[nxt.first][nxt.second][cur.wall_break + 1]) {
								que.push(node(cur.position, cur.get_next_day(), cur.move_count + 1, cur.wall_break, true));
							}
						}
					}
				}
			}
		}
	}


	cout << res;

	return 0;
}