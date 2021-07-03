#include <iostream>
#include <vector>

using namespace std;

const int NOT_CALCULATED = -1;

vector<int> argi;
vector<int> min_span;
vector<vector<int>> parent;

int get_min_time(int root) {
	if (min_span[root] == NOT_CALCULATED) {
		int max_val = 0;
		for (uint32_t i = 0; i < parent[root].size(); i++) {
			int tmp_val = get_min_time(parent[root][i]);

			if (tmp_val > max_val) {
				max_val = tmp_val;
			}
		}

		min_span[root] = argi[root] + max_val;
	}
	
	return min_span[root];
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int t;
	cin >> t;
	while (t-- > 0) {
		int n, k, w;
		cin >> n >> k;
		argi = vector<int>(n + 1);
		min_span = vector<int>(n + 1, NOT_CALCULATED);
		parent = vector<vector<int>>(n + 1);
		for (int i = 1; i <= n; i++) {
			cin >> argi[i];
		}
		for (int i = 0, frt, bck; i < k; i++) {
			cin >> frt >> bck;
			parent[bck].push_back(frt);
		}
		cin >> w;

		cout << get_min_time(w) << '\n';
	}


	return 0;
}