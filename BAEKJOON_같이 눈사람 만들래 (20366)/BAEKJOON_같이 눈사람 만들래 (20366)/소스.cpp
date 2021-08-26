#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

struct node {
	int n1, n2;
	int sum;
	node(int _n1 = 0, int _n2 = 0, int _s = 0) : n1(_n1), n2(_n2), sum(_s) {}
};

int n;
vector<int> argi;
vector<node> snowman;

bool operator<(const node& a, const node& b) {
	return a.sum < b.sum;
}

bool operator!=(const node& a, const node& b) {
	return !(a.n1 == b.n1 || a.n2 == b.n2 || a.n1 == b.n2 || a.n2 == b.n1);
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	argi.resize(n);
	for (int& i : argi) {
		cin >> i;
	}

	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			snowman.push_back(node(i, j, argi[i] + argi[j]));
		}
	}

	int min_dist = INT32_MAX;
	sort(snowman.begin(), snowman.end());
	for (size_t i = 0; i < snowman.size() - 1; i++) {
		for (size_t j = i + 1; j < snowman.size(); j++) {
			if (snowman[i] != snowman[j]) {
				min_dist = min(min_dist, abs(snowman[i].sum - snowman[j].sum));
				break;
			}
		}
	}

	cout << min_dist;

	return 0;
}