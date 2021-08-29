#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

const int MOD = 10;
const char EMPTY = '0';
const char WALL = '1';
const vector<pint> poss_dir = {
	make_pair(1, 0),
	make_pair(-1, 0),
	make_pair(0, 1),
	make_pair(0, -1)
};

int n, m;
vector<vector<char>> board;
vector<vector<bool>> visit;
vector<vector<pint>> parent;
vector<vector<int>> set_size;
queue<pint> que;

const pint operator+(const pint& a, const pint& b) {
	return make_pair(a.first + b.first, a.second + b.second);
}

bool in_range(const pint& p) {
	if (0 <= p.first && p.first < n && 0 <= p.second && p.second < m) {
		return true;
	}
	return false;
}

pint _find(const pint& p) {
	if (parent[p.first][p.second] == p) {
		return p;
	}
	else {
		return parent[p.first][p.second] = _find(parent[p.first][p.second]);
	}
}

void _union(const pint &x, const pint &y) {
	pint f_x = _find(x), f_y = _find(y);
	if (f_x > f_y) {
		swap(f_x, f_y);
	}
	set_size[f_x.first][f_x.second] += set_size[f_y.first][f_y.second];
	set_size[f_y.first][f_y.second] = 0;
	parent[f_y.first][f_y.second] = f_x;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> m;
	board = vector<vector<char>>(n, vector<char>(m));
	visit = vector<vector<bool>>(n, vector<bool>(m, false));
	parent = vector<vector<pint>>(n, vector<pint>(m));
	set_size = vector<vector<int>>(n, vector<int>(m));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> board[i][j];

			parent[i][j] = make_pair(i, j);
			set_size[i][j] = (board[i][j] == EMPTY ? 1 : 0);
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (set_size[i][j] != 0) {
				visit[i][j] = true;
				que.push(make_pair(i, j));

				while (!que.empty()) {
					pint cur = que.front();
					que.pop();

					for (const pint& dir : poss_dir) {
						pint nxt = cur + dir;

						if (in_range(nxt) && board[nxt.first][nxt.second] == EMPTY && !visit[nxt.first][nxt.second]) {
							visit[nxt.first][nxt.second] = true;
							_union(cur, nxt);
							que.push(nxt);
						}
					}
				}
			}
		}
	}

	for (int i = 0, tmp_sum; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] == EMPTY) {
				cout << 0;
			}
			else {
				tmp_sum = 1;
				vector<pint> adj;

				for (const pint& dir : poss_dir) {
					pint tmp = make_pair(i, j) + dir;

					if (in_range(tmp) && board[tmp.first][tmp.second] == EMPTY) {
						adj.push_back(_find(tmp));
					}
				}

				sort(adj.begin(), adj.end());
				adj.erase(unique(adj.begin(), adj.end()), adj.end());
				for (pint& p : adj) {
					tmp_sum += set_size[p.first][p.second];
				}
				cout << tmp_sum % MOD;
			}
		}
		cout << '\n';
	}

	return 0;
}