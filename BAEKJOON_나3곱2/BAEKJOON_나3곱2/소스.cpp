#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

typedef long long lli;

vector<lli> bfs(lli start, vector<lli>& argi) {
	queue<vector<lli>> que;
	que.push(vector<lli>(1, start));
	while (!que.empty()) {
		vector<lli> cur = que.front();
		que.pop();

		if (cur.size() == argi.size()) {
			return cur;
		}


		bool is_divided = (cur.back() % 3 == 0);
		lli to_test = cur.back() / 3;
		if (is_divided && binary_search(argi.begin(), argi.end(), to_test) && !binary_search(cur.begin(), cur.end(), to_test)) {
			vector<lli> tmp = cur;
			tmp.push_back(to_test);
			que.push(tmp);
		}
		to_test = cur.back() * 2;
		if (binary_search(argi.begin(), argi.end(), to_test) && !binary_search(cur.begin(), cur.end(), to_test)) {
			vector<lli> tmp = cur;
			tmp.push_back(to_test);
			que.push(tmp);
		}
	}

	return vector<lli>();
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n;
	cin >> n;
	vector<lli> argi(n);
	for (lli& i : argi) {
		cin >> i;
	}
	sort(argi.begin(), argi.end());

	vector<lli> bfs_res;
	for (int i = 0; i < n; i++) { 
		vector<lli> tmp = bfs(argi[i], argi);
		if (!tmp.empty()) {
			bfs_res = tmp;
			break;
		}
	}

	for (lli& i : bfs_res) {
		cout << i << ' ';
	}

	return 0;
}