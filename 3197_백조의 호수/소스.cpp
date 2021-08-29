#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pint;

vector<pint> dir = {
	{1, 0}, {-1, 0}, {0, 1}, {0, -1}
};
const char EMPTY = '.';
const char ICE = 'X';
const char SWAN = 'L';

int r, c;
vector<pint> swan_pos;
vector<vector<pint>> parent;
vector<vector<bool>> visit;
vector<vector<char>> board;
queue<pint> melting;

bool in_range(pint& p) {
	if (0 <= p.first && p.first < r && 0 <= p.second && p.second < c) {
		return true;
	}
	return false;
}

pint _find(pint& p) {
	if (parent[p.first][p.second] == p) {
		return p;
	}
	return parent[p.first][p.second] = _find(parent[p.first][p.second]);
}

void _union(pint& x, pint& y) {
	pint f_x = _find(x), f_y = _find(y);
	if (f_x > f_y) {
		swap(f_x, f_y);
	}
	parent[f_y.first][f_y.second] = f_x;
}

void init_parent() {
	queue<pint> que;
	parent = vector<vector<pint>>(r, vector<pint>(c));
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			parent[i][j].first = i;
			parent[i][j].second = j;
		}
	}
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (board[i][j] != ICE && !visit[i][j]) {
				visit[i][j] = true;
				que.push(make_pair(i, j));
				
				while (!que.empty()) {
					pint cur = que.front();
					que.pop();
					for (pint& p : dir) {
						pint nxt = make_pair(cur.first + p.first, cur.second + p.second);

						if (in_range(nxt) && !visit[nxt.first][nxt.second]) {
							visit[nxt.first][nxt.second] = true;
							if (board[nxt.first][nxt.second] != ICE) {
								_union(cur, nxt);
								que.push(nxt);
							}
							else {
								melting.push(nxt);
							}
						}
					}
				}
			}
		}
	}
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	cin >> r >> c;
	board = vector<vector<char>>(r, vector<char>(c));
	visit = vector<vector<bool>>(r, vector<bool>(c, false));
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> board[i][j];
			if (board[i][j] == SWAN) {
				swan_pos.push_back(make_pair(i, j));
			}
		}
	}
	init_parent();

	int time_count = 0;
	while (true) {
		if (_find(swan_pos.front()) == _find(swan_pos.back())) {
			break;
		}
		else {
			size_t melt_size = melting.size();
			for (size_t i = 0; i < melt_size; i++) {
				pint cur = melting.front();
				board[cur.first][cur.second] = EMPTY;
				melting.pop();

				for (pint& p : dir) {
					pint nxt = make_pair(cur.first + p.first, cur.second + p.second);

					if (in_range(nxt)) {
						if (board[nxt.first][nxt.second] != ICE) {
							_union(cur, nxt);
						}
						else {
							if (!visit[nxt.first][nxt.second]) {
								visit[nxt.first][nxt.second] = true;
								melting.push(nxt);
							}
						}
					}
				}
			}

			time_count++;
		}
	}
	
	cout << time_count;

	return 0;
}