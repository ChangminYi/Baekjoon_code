#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;
typedef long long lint;

pint operator+ (pint a, pint b) {
	return { a.first + b.first, a.second + b.second };
}

bool isInRange(const pint dir, const int size) {
	if (0 <= dir.first && dir.first < size && 0 <= dir.second && dir.second < size) {
		return true;
	}
	return false;
}

bool isInValue(const pint &cur, const pint &nDir, const int _min, const int _max, const vector<vector<int>> &argi) {
	if (abs(argi[cur.first][cur.second] - argi[nDir.first][nDir.second]) >= _min) {
		if (abs(argi[cur.first][cur.second] - argi[nDir.first][nDir.second]) <= _max) {
			return true;
		}
	}
	return false;
}


int main() {
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);

	const vector<pint> move = {
		{1, 0}, {-1, 0}, {0, 1}, {0, -1}
	};

	int N = 0, L = 0, R = 0;
	cin >> N >> L >> R;
	vector<vector<int>> map(N, vector<int>(N));
	for (vector<int> &i : map) {
		for (int &j : i) {
			cin >> j;
		}
	}

	int counter = 0;
	while (true) {
		vector<vector<pint>> area;
		vector<vector<bool>> visit(N, vector<bool>(N, false));

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (!visit[i][j]) {
					vector<pint> tempArea;
					queue<pint> qu;

					qu.push({ i, j });
					while (!qu.empty()) {
						pint curr = qu.front();
						qu.pop();
						if (!visit[curr.first][curr.second]) {
							visit[curr.first][curr.second] = true;
							tempArea.push_back(curr);

							for (uint32_t k = 0; k < move.size(); k++) {
								pint newPos = curr + move[i];
								if (isInRange(newPos, N) && isInValue(curr, newPos, L, R, map) && !visit[newPos.first][newPos.second]) {
									qu.push(newPos);
								}
							}
						}
					}

					if (tempArea.size() > 1) {
						area.push_back(tempArea);
					}
				}
			}
		}

		if (area.empty()) {
			break;
		}
		else {
			counter++;

			for (uint32_t i = 0; i < area.size(); i++) {
				lint sum = 0;

				for (pint &j : area[i]) {
					sum += map[j.first][j.second];
				}

				int mid = (int)((long double)sum / area[i].size());
				for (pint &j : area[i]) {
					map[j.first][j.second] = mid;
				}
			}
		}
	}

	cout << counter;

	return 0;
}