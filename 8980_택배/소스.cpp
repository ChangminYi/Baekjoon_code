#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct node {
	int start = 0, end = 0;
	int weight = 0;
};

int n, m, max_cap;
vector<node> arg;
vector<int> cap;

bool operator<(const node& a, const node& b) {
	return (a.end == b.end ? a.start < b.start : a.end < b.end);
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n >> max_cap >> m;

	arg.resize(m);
	cap.resize(n, 0);
	for (node& n : arg) {
		cin >> n.start >> n.end >> n.weight;
	}

	sort(arg.begin(), arg.end());

	int total_sum = 0;
	for (const node& cur: arg) {
		int cur_weight = 0;
		for (int j = cur.start; j < cur.end; j++) {
			cur_weight = max(cur_weight, cap[j]);
		}

		int left_weight = min(cur.weight, max_cap - cur_weight);
		total_sum += left_weight;
		for (int j = cur.start; j < cur.end; j++) {
			cap[j] += left_weight;
		}
	}

	cout << total_sum;

	return 0;
}