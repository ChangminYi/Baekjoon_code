#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> pint;

vector<vector<char>> board;
vector<vector<pint>> parent;
vector<vector<bool>> is_parent;

pint get_dir(char c) {
	switch (c) {
	case 'D':
		return make_pair(1, 0);
	case 'U':
		return make_pair(-1, 0);
	case 'R':
		return make_pair(0, 1);
	case 'L':
		return make_pair(0, -1);
	}
	return make_pair(0, 0);
}

pint _find(const pint &x) {
	if (parent[x.first][x.second] == x) {
		return x;
	}
	else {
		return parent[x.first][x.second] = _find(parent[x.first][x.second]);
	}
}

void _union(pint x, pint y) {
	pint f_x = _find(x);
	pint f_y = _find(y);

	if (f_x > f_y) {
		swap(f_x, f_y);
	}

	parent[f_y.first][f_y.second] = f_x;
}

pint operator+(const pint& a, const pint& b) {
	return make_pair(a.first + b.first, a.second + b.second);
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	int n, m;
	cin >> n >> m;
	board = vector<vector<char>>(n, vector<char>(m));
	parent = vector<vector<pint>>(n, vector<pint>(m));
	is_parent = vector<vector<bool>>(n, vector<bool>(m, false));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> board[i][j];
			parent[i][j] = make_pair(i, j);
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			pint cur = make_pair(i, j);
			pint nxt = cur + get_dir(board[i][j]);

			_union(cur, nxt);
		}
	}

	int res = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			pint par_cur = _find(make_pair(i, j));

			if (!is_parent[par_cur.first][par_cur.second]) {
				is_parent[par_cur.first][par_cur.second] = true;
				res++;
			}
		}
	}

	cout << res;

	return 0;
}