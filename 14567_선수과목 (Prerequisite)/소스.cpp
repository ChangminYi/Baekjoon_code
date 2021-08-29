#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int N = 0, K = 0;
	cin >> N >> K;
	vector<vector<int>> tree(N + 1);
	vector<int> argi(N + 1, 1);
	for (int i = 0, temp[2]; i < K; i++) {
		cin >> temp[0] >> temp[1];
		tree[temp[0]].push_back(temp[1]);
	}

	for (uint32_t i = 1; i < tree.size(); i++) {
		for (uint32_t j = 0; j < tree[i].size(); j++) {
			argi[tree[i][j]] = max(argi[i] + 1, argi[tree[i][j]]);
		}
	}

	for (uint32_t i = 1; i < argi.size(); i++) {
		cout << argi[i] << ' ';
	}

	return 0;
}