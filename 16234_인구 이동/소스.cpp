#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;
typedef pair<int, int> pint;

const int MAX = 50;
int land[MAX][MAX];
int n, L, R;
vector<pint> adj = {
	{1, 0}, {-1, 0}, {0, 1}, {0, -1}
};


bool in_range(const pint& p) {
	if (0 <= p.first && p.first < n) {
		if (0 <= p.second && p.second < n) {
			return true;
		}
	}
	return false;
}

bool can_open(const pint& a, const pint& b) {
	int sub = abs(land[a.first][a.second] - land[b.first][b.second]);
	if (L <= sub && sub <= R) {
		return true;
	}
	else {
		return false;
	}
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	cin >> n >> L >> R;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> land[i][j];
		}
	}

	int move_count = 0;
	while (true) {
		bool change = false;
		vector<vector<bool>> check(n, vector<bool>(n, false));
		vector<vector<pint>> to_change;
		queue<pint> que;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {

				for (pint& pos : adj) {
					pint new_pos = { i + pos.first, j + pos.second };

					if (in_range(new_pos) && can_open({ i, j }, new_pos) && !check[new_pos.first][new_pos.second]) {
						change = true;

						check[i][j] = true;
						to_change.push_back({ make_pair(i, j) });
						que.push({ i, j });
						while (!que.empty()) {
							pint cur = que.front();
							que.pop();

							for (pint& to_see : adj) {
								pint temp = { cur.first + to_see.first, cur.second + to_see.second };

								if (in_range(temp) && can_open(cur, temp) && !check[temp.first][temp.second]) {
									check[temp.first][temp.second] = true;
									to_change.back().push_back(temp);
									que.push(temp);
								}
							}
						}
					}
				}

			}
		}

		for (vector<pint>& argi : to_change) {
			int sum = 0;
			for (pint& i : argi) {
				sum += land[i.first][i.second];
			}

			sum /= argi.size();
			for (pint& i : argi) {
				land[i.first][i.second] = sum;
			}
		}

		if (!change) {
			break;
		}
		else {
			//move_count += to_change.size();
			move_count++;
		}
	}

	cout << move_count;

	return 0;
}