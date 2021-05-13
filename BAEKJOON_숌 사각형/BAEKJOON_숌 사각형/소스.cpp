//사전 순으로 가장 빠른 게 어떤 기준인지 모르겠음

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void printLine(vector<int> &argi) {
	for (int i = 0; i < argi.size() - 1; i++) {
		cout << argi[i] << ' ';
	}
	cout << argi.back() << '\n';
}

bool comp(vector<int> &a, vector<int> &b) {
	return a.front() < b.front();
}

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);
	cout.tie(NULL);
	cout.sync_with_stdio(false);

	int N = 0, D = 0;
	cin >> N >> D;
	vector<vector<int>> argi = vector<vector<int>>(N);
	for (vector<int> &v : argi) {
		v.assign(N, 0);
	}

	for (int i = 0; i < N; i++) {
		argi[0][i] = i % D;
	}

	for (int i = 1; i < N; i++) {
		argi[i][N - 1] = argi[i - 1][0];
		for (int j = 0; j < N - 1; j++) {
			argi[i][j] = argi[i - 1][j + 1];
		}
	}

	sort(argi.begin(), argi.end(), comp);

	for (vector<int> &i : argi) {
		printLine(i);
	}

	return 0;
}