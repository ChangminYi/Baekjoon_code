#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n;
	cin >> n;

	vector<int> argi(n);
	for (int& i : argi) {
		cin >> i;
	}

	vector<int> res;
	for (int& i : argi) {
		if (res.empty()) {
			res.push_back(i);
		}
		else if (i < res.front()) {
			res[0] = i;
		}
		else if (i > res.back()) {
			res.push_back(i);
		}
		else {
			vector<int>::iterator iter = upper_bound(res.begin(), res.end(), i - 1);
			*iter = i;
		}
	}

	cout << res.size();

	return 0;
}