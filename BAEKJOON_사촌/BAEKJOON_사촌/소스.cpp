#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <map>

using namespace std;

bool is_in_vector(int to_find, const vector<int>& argi) {
	int lft = 0, rgt = argi.size() - 1;
	while (lft <= rgt) {
		int mid = (lft + rgt) / 2;
		if (argi[mid] == to_find) {
			return true;
		}
		else {
			if (argi[mid] < to_find) {
				lft = mid + 1;
			}
			else {
				rgt = mid - 1;
			}
		}
	}
	return false;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n, k;
	while (true) {
		cin >> n >> k;
		if (n == 0 && k == 0) {
			break;
		}

		deque<int> node(n);
		for (int& i : node) {
			cin >> i;
		}

		queue<vector<int>> chunk;
		chunk.push(vector<int>(1, node.front()));
		node.pop_front();
		while (!node.empty()) {
			vector<int> child_chunk = { node.front() };
			node.pop_front();

			while (!node.empty() && child_chunk.back() + 1 == node.front()) {
				child_chunk.push_back(node.front());
				node.pop_front();
			}

			chunk.push(child_chunk);
		}

		map<int, vector<int>> tree;
		map<int, int> rev_tree;
		queue<int> match_parent;
		match_parent.push(chunk.front().front());
		chunk.pop();
		while (!chunk.empty()) {
			int become_parent = match_parent.front();
			vector<int> become_child = chunk.front();

			tree.insert(make_pair(become_parent, become_child));
			for (int& i : become_child) {
				match_parent.push(i);
				rev_tree.insert(make_pair(i, become_parent));
			}

			match_parent.pop();
			chunk.pop();
		}

		int k_par = 0, k_grd = 0;
		if (rev_tree.find(k) == rev_tree.end()) {
			cout << 0 << '\n';
		}
		else {
			k_par = rev_tree[k];

			if (rev_tree.find(k_par) == rev_tree.end()) {
				cout << 0 << '\n';
			}
			else {
				k_grd = rev_tree[k_par];

				int cousin_sum = 0;
				for (int i = 0; i < tree[k_grd].size(); i++) {
					vector<int> group = tree[tree[k_grd][i]];

					if (!group.empty() && !is_in_vector(k, group)) {
						cousin_sum += tree[tree[k_grd][i]].size();
					}
				}

				cout << cousin_sum << '\n';
			}
		}
	}


	return 0;
}