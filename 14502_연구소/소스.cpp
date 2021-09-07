#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pint;

const vector<pint> poss_dir = {
	make_pair(0, 1),
	make_pair(1, 0),
	make_pair(0, -1),
	make_pair(-1, 0)
};
const int EMPTY = 0;
const int WALL = 1;
const int VIRUS = 2;

int n, m, res = 0;
vector<vector<int>> board, simul_b;
vector<pint> dir_virus, dir_empty;
queue<pint> que;

pint operator+(const pint& lhs, const pint& rhs){
	return make_pair(lhs.first + rhs.first, lhs.second + rhs.second);
}

bool in_range(const pint& p) {
	return 0 <= p.first && p.first < n && 0 <= p.second && p.second < m;
}

int bfs() {
	for (const pint& v : dir_virus) {
		que.push(v);
	}

	while (!que.empty()) {
		pint cur = que.front();
		que.pop();

		for (const pint& dir : poss_dir) {
			pint nxt = cur + dir;

			if (in_range(nxt) && simul_b[nxt.first][nxt.second] == EMPTY) {
				simul_b[nxt.first][nxt.second] = VIRUS;
				que.push(nxt);
			}
		}
	}

	int empty_cnt = 0;
	for (const vector<int>& row : simul_b) {
		for (const int& i : row) {
			if (i == EMPTY) {
				empty_cnt++;
			}
		}
	}

	return empty_cnt;
}

void copy_board(const vector<vector<int>>& from, vector<vector<int>>& to) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			to[i][j] = board[i][j];
		}
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> m;
	board.resize(n, vector<int>(m));
	simul_b.resize(n, vector<int>(m));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> board[i][j];

			if (board[i][j] == EMPTY) {
				dir_empty.push_back(make_pair(i, j));
			}
			else if (board[i][j] == VIRUS) {
				dir_virus.push_back(make_pair(i, j));
			}
		}
	}

	/*
	* 원래 연구소의 빈 칸들만 탐색하여 벽을 세움
	* 벽은 정확히 3개만을 써야 해서 3중 for문으로 모든 빈칸 조합 탐색
	* 판을 다른 배열에 복제해서 bfs를 하고, 최댓값 업데이트
	*/
	for (size_t i = 0; i < dir_empty.size() - 2; i++) {
		for (size_t j = i + 1; j < dir_empty.size() - 1; j++) {
			for (size_t k = j + 1; k < dir_empty.size(); k++) {
				copy_board(board, simul_b);
				simul_b[dir_empty[i].first][dir_empty[i].second] = WALL;
				simul_b[dir_empty[j].first][dir_empty[j].second] = WALL;
				simul_b[dir_empty[k].first][dir_empty[k].second] = WALL;

				res = max(res, bfs());
			}
		}
	}

	cout << res;

	return 0;
}