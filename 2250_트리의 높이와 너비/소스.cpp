#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int NO_CHILD = -1;

typedef struct NODE {
	int left_child, right_child;
}node;

void get_level(int root, vector<node>& tree, vector<vector<int>>& span, int level) {
	if (span.size() == level) {
		span.push_back(vector<int>(1, root));
	}
	else {
		span[level].push_back(root);
	}


	if (tree[root].left_child != NO_CHILD) {
		get_level(tree[root].left_child, tree, span, level + 1);
	}
	if (tree[root].right_child != NO_CHILD) {
		get_level(tree[root].right_child, tree, span, level + 1);
	}
}

void get_span(int root, vector<node>& tree, vector<int>& span) {
	static int counter = 1;
	if (tree[root].left_child != NO_CHILD) {
		get_span(tree[root].left_child, tree, span);
	}

	span[root] = counter++;

	if (tree[root].right_child != NO_CHILD) {
		get_span(tree[root].right_child, tree, span);
	}
}

int find_root(vector<int>& argi) {
	for (int i = 1; i < argi.size(); i++) {
		if (argi[i] == 1) {
			return i;
		}
	}
	return 0;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n;
	cin >> n;

	vector<int> root_counter(n + 1, 0);
	vector<node> tree(n + 1);
	for (int i = 0, cur, lft, rgt; i < n; i++) {
		cin >> cur >> lft >> rgt;
		tree[cur].left_child = lft;
		tree[cur].right_child = rgt;

		root_counter[cur]++;
		if (lft != NO_CHILD) {
			root_counter[lft]++;
		}
		if (rgt != NO_CHILD) {
			root_counter[rgt]++;
		}
	}

	int root = find_root(root_counter);
	vector<int> span(n + 1);
	vector<vector<int>> level;
	get_span(root, tree, span);
	get_level(root, tree, level, 0);

	int max_lev = 0, max_val = 0;
	for (uint32_t i = 0; i < level.size(); i++) {
		int tmp_max = -1, tmp_min = INT32_MAX;

		for (int& j : level[i]) {
			if (span[j] > tmp_max) {
				tmp_max = span[j];
			}
			if (span[j] < tmp_min) {
				tmp_min = span[j];
			}
		}

		if (tmp_max - tmp_min > max_val) {
			max_val = tmp_max - tmp_min;
			max_lev = i;
		}
	}

	cout << max_lev + 1 << ' ' << max_val + 1;

	return 0;
}