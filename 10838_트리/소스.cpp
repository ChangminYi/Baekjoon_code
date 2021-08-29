#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

const int NO_PARENT = -1;
const int MAX_COLOR = 100000;

vector<int> parent;
vector<int> edge;
vector<int> check = vector<int>(MAX_COLOR);
unordered_set<int> color;
int par_count = 0;

int get_lca(int v1, int v2) {
	if (v1 == v2) {
		return v1;
	}
	else {
		par_count++;

		for (int i = 0; i <= 1000; i++) {
			if (v1 != 0) {
				if (check[v1] == par_count) {
					return v1;
				}
				else {
					check[v1] = par_count;
					v1 = parent[v1];
				}
			}
			if (v2 != 0) {
				if (check[v2] == par_count) {
					return v2;
				}
				else {
					check[v2] = par_count;
					v2 = parent[v2];
				}
			}
			if (v1 == v2 && v1 == 0) {
				return v1;
			}
		}
	}

	return NO_PARENT;
}

void paint(int v1, int v2, int new_color) {
	int lca = get_lca(v1, v2);

	for (int cur = v1; cur != lca; cur = parent[cur]) {
		edge[cur] = new_color;
	}
	for (int cur = v2; cur != lca; cur = parent[cur]) {
		edge[cur] = new_color;
	}

	return;
}

void move(int v1, int v2) {
	parent[v1] = v2;

	return;
}

size_t count(int v1, int v2) {
	color.clear();
	int lca = get_lca(v1, v2);

	for (int cur = v1; cur != lca; cur = parent[cur]) {
		color.insert(edge[cur]);
	}
	for (int cur = v2; cur != lca; cur = parent[cur]) {
		color.insert(edge[cur]);
	}

	return color.size();
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n, k;
	cin >> n >> k;

	parent = vector<int>(n);
	parent[0] = NO_PARENT;
	edge = vector<int >(n, 0);

	do {
		int inst, arg1, arg2, arg3;
		cin >> inst >> arg1 >> arg2;

		if (inst == 1) {
			cin >> arg3;
			paint(arg1, arg2, arg3);
		}
		else if (inst == 2) {
			move(arg1, arg2);
		}
		else {
			cout << count(arg1, arg2) << '\n';
		}
	} while (--k > 0);

	return 0;
}