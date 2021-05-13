#include <iostream>
#include <vector>
using namespace std;

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);

	int N = 0, M = 0, K = 0;
	cin >> N >> M >> K;

	vector<vector<int>> argi = vector<vector<int>>(N, vector<int>(M));
	vector<int> count = vector<int>(N, 0);
	for (vector<int> &i : argi) {
		for (int &j : i) {
			cin >> j;
		}
	}
	
	for (int j = 0; j < M; j++) {
		for (int i = 0; i < N; i++) {
			count[i] += argi[i][j];

			if (count[i] >= K) {
				cout << i + 1 << ' ' << j + 1;
				return 0;
			}
		}
	}


	return 0;
}