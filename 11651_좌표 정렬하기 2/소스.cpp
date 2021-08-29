#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool comp(const pair<int, int> &a, const pair<int, int> &b) {
	if (a.second == b.second) {
		return (a.first < b.first);
	}
	return a.second < b.second;
}

int main() {
	cin.tie(nullptr); cout.tie(nullptr);
	cin.sync_with_stdio(false); cout.sync_with_stdio(false);

	int N = 0;
	cin >> N;

	vector<pair<int, int>> coord(N);
	for (pair<int, int> &i : coord) {
		cin >> i.first >> i.second;
	}

	sort(coord.begin(), coord.end(), comp);

	for (pair<int, int> &i : coord) {
		cout << i.first << ' ' << i.second << '\n';
	}

	return 0;
}