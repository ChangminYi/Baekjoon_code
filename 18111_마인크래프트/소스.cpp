#include <iostream>
#include <vector>
using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int N = 0, M = 0, B = 0;
	cin >> N >> M >> B;

	int minh = 0x07fffffff, maxh = 0;
	vector<vector<int>> tile = vector<vector<int>>(N, vector<int>(M));
	for (vector<int> &i : tile) {
		for (int &j : i) {
			cin >> j;
			if (minh > j) { minh = j; }
			else if (maxh < j) { maxh = j; }
		}
	}

	int finalTime = 0x7FFFFFFF, finalHeight = 0;
	for (int curH = minh, tempB, totalTime; curH <= maxh; curH++) {
		vector<vector<int>> tempTile(tile);
		tempB = B;
		totalTime = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (tempTile[i][j] > curH) {
					totalTime += 2 * (tempTile[i][j] - curH);
					tempB += (tempTile[i][j] - curH);
					tempTile[i][j] = curH;
				}
			}
		}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (tempTile[i][j] < curH) {
					totalTime += (curH - tempTile[i][j]);
					tempB -= (curH - tempTile[i][j]);
				}
			}
		}

		if (tempB >= 0) {
			if (finalTime >= totalTime) {
				finalTime = totalTime;
				finalHeight = curH;
			}
		}
	}

	cout << finalTime << ' ' << finalHeight;

	return 0;
}