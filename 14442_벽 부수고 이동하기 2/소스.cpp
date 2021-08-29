#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <string>

using namespace std;

typedef tuple<int, int, int> coor;
typedef pair<coor, int> node;
typedef pair<int, int> pint;

const vector<pint> dir = {
	{1, 0}, {-1, 0}, {0, 1}, {0, -1}
};
const int NOT_FOUND = -1;
const int NOT_VISIT = 0;
const char EMPTY = '0';
const char WALL = '1';
int n, m, k;
vector<string> board;
vector<vector<vector<int>>> visit;
queue<node> que;

bool in_range(const pint& p) {
	if (0 <= p.first && p.first < n && 0 <= p.second && p.second < m) {
		return true;
	}
	return false;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	cin >> n >> m >> k;
	board = vector<string>(n);
	visit = vector<vector<vector<int>>>(n, vector<vector<int>>(m, vector<int>(k + 1, NOT_VISIT)));
	for (string& s : board) {
		cin >> s;
	}

	int min_move = NOT_FOUND;
	que.push(make_pair(make_tuple(0, 0, 0), 1));
	visit[0][0][0] = 1;
	while (!que.empty()) {
		coor cur = que.front().first;
		int mov = que.front().second;
		que.pop();

		if (get<0>(cur) == n - 1 && get<1>(cur) == m - 1) {
			min_move = mov;
			break;
		}
		else {
			for (const pint& p : dir) {
				pint nxt = make_pair(get<0>(cur) + p.first, get<1>(cur) + p.second);

				if (in_range(nxt)) {
					if (board[nxt.first][nxt.second] == EMPTY) {
						if (visit[nxt.first][nxt.second][get<2>(cur)] == NOT_VISIT) {
							visit[nxt.first][nxt.second][get<2>(cur)] = mov + 1;
							que.push(make_pair(make_tuple(nxt.first, nxt.second, get<2>(cur)), mov + 1));
						}
					}
					else if(get<2>(cur) < k) {
						if (visit[nxt.first][nxt.second][get<2>(cur) + 1] == NOT_VISIT) {
							visit[nxt.first][nxt.second][get<2>(cur) + 1] = mov + 1;
							que.push(make_pair(make_tuple(nxt.first, nxt.second, get<2>(cur) + 1), mov + 1));
						}
					}
				}
			}
		}
	}

	if (min_move == NOT_FOUND) {
		cout << -1;
	}
	else {
		cout << min_move;
	}

	return 0;
}