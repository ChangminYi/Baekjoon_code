#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int getcount(vector<vector<bool>> &origin, vector<vector<bool>> &toComp, int row, int col) {
	int count = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (origin[row + i][col + j] == toComp[i][j]) {
				count++;
			}
		}
	}
	return count;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int N = 0, M = 0;
	cin >> N >> M;
	vector<vector<bool>> table = vector<vector<bool>>(N, vector<bool>(M, false));
	for (int i = 0; i < N; i++) {
		string temp;
		cin >> temp;

		for (uint32_t j = 0; j < temp.size(); j++) {
			if (temp[j] == 'W') {
				table[i][j] = true;
			}
		}
	}

	vector<vector<bool>> eight = vector<vector<bool>>(8, vector<bool>(8, false));
	vector<vector<bool>> reverse = vector<vector<bool>>(8, vector<bool>(8, false));
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if ((i + j) % 2 == 0) {
				eight[i][j] = true;
			}
			reverse[i][j] = !eight[i][j];
		}
	}

	int res = 0x7fffffff;
	for (int i = 0; i <= N - 8; i++) {
		for (int j = 0; j <= M - 8; j++) {
			res = min(res, min(getcount(table, eight, i, j), getcount(table, reverse, i, j)));
		}
	}
	cout << res;

	return 0;
}