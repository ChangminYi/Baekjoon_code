#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void DFS(int current, vector<vector<int>> &tree, vector<bool> &visit, int &count) {
	visit[current] = true;

	for (uint32_t i = 0; i < tree[current].size(); i++) {
		if (visit[tree[current][i]] == false) {
			DFS(tree[current][i], tree, visit, ++count);
		}
	}
}

int main(void) {
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int N = 0, M = 0, tempMax = 0;
	cin >> N >> M;
	vector<bool> visit;
	vector<vector<int>> Computer(N);

	for (int i = 0, a, b; i < M; i++) {
		cin >> a >> b;
		Computer[--b].push_back(--a);
	}

	vector<int> answer;
	for (int i = 1, num; i <= N; i++) {
		visit.assign(N, false);
		num = 0;
		DFS(i - 1, Computer, visit, num);

		if (answer.empty()) {
			tempMax = num;
			answer.push_back(i);
		}
		else if(num == tempMax) {
			answer.push_back(i);
		}
		else if (num > tempMax) {
			tempMax = num;
			answer = vector<int>(1, i);
		}
	}

	sort(answer.begin(), answer.end());
	for (int i : answer) {
		cout << i << ' ';
	}

	return 0;
}