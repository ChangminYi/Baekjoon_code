#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, c;
vector<int> stuff;
vector<int> set1, set2;

void dfs(int cur, int end, vector<int>& argi, int sum) {
	if (sum > c) {
		return;
	}
	else {
		if (cur > end) {
			argi.push_back(sum);
			return;
		}
		else {
			dfs(cur + 1, end, argi, sum);
			dfs(cur + 1, end, argi, sum + stuff[cur]);
		}
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> c;
	stuff = vector<int>(n);
	for (int& i : stuff) {
		cin >> i;
	}

	dfs(0, n / 2 - 1, set1, 0);
	dfs(n / 2, n - 1, set2, 0);
	// sort(set1.begin(), set1.end());
	sort(set2.begin(), set2.end());

	int cnt = 0;
	for (int& val : set1) {
		auto up_b = upper_bound(set2.begin(), set2.end(), c - val);
		cnt += distance(set2.begin(), up_b);
	}

	cout << cnt;

	return 0;
}