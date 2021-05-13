#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// 자식 노드를 dfs를 이용하여 센다.
// 자식 노드가 1개 있으면, 해당 노드가 삭제할 노드인지 확인한다.
void how_many_leaf(vector<vector<int>> &tree, int current, int toDelete, int &answer) {
	if (toDelete == current) {
		return;
	}
	else {
		if (tree[current].empty()) {
			answer++;
		}
		else if (tree[current].size() == 1) {
			if (tree[current].front() == toDelete) {
				answer++;
			}
		}
		else {
			for (uint32_t i = 0; i < tree[current].size(); i++) {
				how_many_leaf(tree, tree[current][i], toDelete, answer);
			}
		}
	}
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int N = 0, root = 0, answer = 0, toDelete = 0;
	cin >> N;
	vector<vector<int>> child_vec(N, vector<int>());

	for (int i = 0; i < N; i++) {
		int parent = 0; 
		cin >> parent;
		if (parent != -1) {
			child_vec[parent].push_back(i);
		}
		else {
			root = i;
		}
	}

	cin >> toDelete;
	how_many_leaf(child_vec, root, toDelete, answer);
	cout << answer;

	return 0;
}