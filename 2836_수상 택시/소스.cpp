#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;
typedef long long lli;

int n, m;
lli total_len = 0;
vector<pint> arg;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> m;
	for (int i = 0, arg1, arg2; i < n; i++) {
		cin >> arg1 >> arg2;
		if (arg1 > arg2) {
			arg.push_back(make_pair(arg2, arg1));
		}
	}

	sort(arg.begin(), arg.end());

	int left = arg[0].first, right = arg[0].second;
	for (int i = 1; i < arg.size(); i++) {
		if (arg[i].first <= right) {
			right = max(right, arg[i].second);
		}
		else {
			total_len += right - left;
			left = arg[i].first;
			right = arg[i].second;
		}
	}
	total_len += right - left;

	cout << m + 2 * total_len;

	return 0;
}