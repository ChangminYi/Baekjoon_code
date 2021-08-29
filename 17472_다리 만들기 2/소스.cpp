#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <numeric>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;
typedef pair<pint, vector<pint>> brid;

const int SEA = 0;
const int LAND = 1;
const vector<pint> poss_dir = {
	make_pair(0, 1),
	make_pair(0, -1),
	make_pair(1, 0),
	make_pair(-1, 0)
};

int n, m, set_idx_count = 0;
vector<vector<bool>> board;
map<pint, int> set_idx;
vector<set<pint>> land_set;
vector<pair<pint, vector<pint>>> land_w_sea;
vector<brid> bridge;
vector<int> parent;

bool brid_cmp(const brid& a, const brid& b) {
	return a.second.size() < b.second.size();
}

int _find(int x) {
	if (parent[x] == x) {
		return x;
	}
	return parent[x] = _find(parent[x]);
}

void _union(int x, int y) {
	int f_x = _find(x), f_y = _find(y);
	if (f_x < f_y) {
		swap(f_x, f_y);
	}
	parent[f_x] = f_y;
}

pint operator+(const pint& a, const pint& b) {
	return make_pair(a.first + b.first, a.second + b.second);
}

bool in_range(const pint &p) {
	if (0 <= p.first && p.first < n) {
		if (0 <= p.second && p.second < m) {
			return true;
		}
	}
	return false;
}

void init_land_set() {
	queue<pint> que;
	vector<vector<bool>> visit(n, vector<bool>(m, false));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] && !visit[i][j]) {
				visit[i][j] = true;

				pint cur = make_pair(i, j);
				set_idx.insert(make_pair(cur, set_idx_count++));
				land_set.push_back(set<pint>());
				land_set.back().insert(cur);
				que.push(cur);

				while (!que.empty()) {
					cur = que.front();
					que.pop();

					for (const pint& dir : poss_dir) {
						pint nxt = cur + dir;
						if (in_range(nxt) && board[nxt.first][nxt.second] && !visit[nxt.first][nxt.second]) {
							land_set.back().insert(nxt);
							set_idx.insert(make_pair(nxt, set_idx[cur]));
							visit[nxt.first][nxt.second] = true;
							que.push(nxt);
						}
					}
				}
			}
		}
	}
}

void init_land_w_sea() {
	for (size_t i = 0; i < land_set.size(); i++) {
		for (auto j = land_set[i].begin(); j != land_set[i].end(); j++) {
			vector<pint> adj_dir;

			for (const pint& dir : poss_dir) {
				pint tmp = *j + dir;
				if (in_range(tmp) && !board[tmp.first][tmp.second]) {
					adj_dir.push_back(dir);
				}
			}

			if (!adj_dir.empty()) {
				land_w_sea.push_back(make_pair(*j, adj_dir));
			}
		}
	}
}

void get_all_bridge() {
	stack<pint> stk;

	for (pair<pint, vector<pint>>& node : land_w_sea) {
		for (pint& dir : node.second) {
			bool find_bridge = false;

			stk.push(node.first);
			while (true) {
				pint nxt = stk.top() + dir;

				if (in_range(nxt)) {
					if (board[nxt.first][nxt.second]) {
						if (set_idx[nxt] != set_idx[node.first]) {
							stk.push(nxt);
							find_bridge = true;
						}
						break;
					}
					else if (!board[nxt.first][nxt.second]) {
						stk.push(nxt);
					}
				}
				else {
					break;
				}
			}

			if (find_bridge && stk.size() >= 4) {
				vector<pint> tiles;
				pint frt = stk.top();

				stk.pop();
				while (stk.size() > 1) {
					tiles.push_back(stk.top());
					stk.pop();
				}
				pint bck = stk.top();
				stk.pop();

				bridge.push_back(make_pair(make_pair(set_idx[frt], set_idx[bck]), tiles));
			}
			else {
				while (!stk.empty()) {
					stk.pop();
				}
			}
		}
	}
}

vector<int> get_mst_bridge() {
	vector<int> bridge_idx;
	parent = vector<int>(set_idx_count);
	
	iota(parent.begin(), parent.end(), 0);
	for (size_t i = 0; i < bridge.size(); i++) {
		brid cur = bridge[i];
		int f_f = _find(cur.first.first);
		int f_s = _find(cur.first.second);
		if (f_f != f_s) {
			_union(f_f, f_s);
			bridge_idx.push_back(i);
		}

		if (bridge_idx.size() == set_idx_count - 1) {
			break;
		}
	}

	return bridge_idx;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> m;
	board = vector<vector<bool>>(n, vector<bool>(m));
	for (int i = 0, tmp; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> tmp;
			board[i][j] = (tmp == 1);
		}
	}

	init_land_set();
	init_land_w_sea();
	get_all_bridge();

	sort(bridge.begin(), bridge.end(), brid_cmp);

	vector<int> mst_idx = get_mst_bridge();

	if (mst_idx.size() < set_idx_count - 1) {
		cout << -1;
	}
	else {
		int total_length = 0;

		for (int idx : mst_idx) {
			total_length += bridge[idx].second.size();
		}

		cout << total_length;
	}

	return 0;
}