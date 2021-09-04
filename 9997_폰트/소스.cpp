#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int ALL_VISIT = (1 << 26) - 1;

int n;
vector<int> str_hash;

int dfs(int idx, int visit) {
	if (idx == n) {
		return (visit == ALL_VISIT ? 1 : 0);
	}
	else {
		return dfs(idx + 1, str_hash[idx] | visit) + dfs(idx + 1, visit);
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	str_hash.resize(n, 0);
	for (int i = 0; i < n; i++) {
		string tmp;
		cin >> tmp;

		for (const char c : tmp) {
			str_hash[i] |= (1 << (c - 'a'));
		}
	}

	cout << dfs(0, 0);

	return 0;
}