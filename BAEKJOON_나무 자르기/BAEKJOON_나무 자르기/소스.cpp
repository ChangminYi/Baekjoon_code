#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int N, M;
ll maxi, res;

ll bin_search(const vector<int>& tree, int left, int right) {
	int mid = (left + right) / 2;
	ll sum = 0;

	if (left > right) {
		return res;
	}
	else {
		for (size_t i = 0; i < tree.size(); i++) {
			if (tree[i] < mid) {
				break;
			}
			else {
				sum += tree[i] - mid;
			}
		}

		if (sum >= M) {
			res = (res < mid) ? mid : res;
		}

		if (sum > M) {
			return bin_search(tree, mid + 1, right);
		}
		else {
			return bin_search(tree, left, mid - 1);
		}
	}
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	cin >> N >> M;
	vector<int> tree(N);
	for (int& i : tree) {
		cin >> i;
	}

	sort(tree.rbegin(), tree.rend());
	maxi = tree.front();

	cout << bin_search(tree, 0, maxi);

	return 0;
}