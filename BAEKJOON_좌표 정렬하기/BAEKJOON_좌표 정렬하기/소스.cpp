#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool comp(pair<int, int> &a, pair<int, int> &b) {
	if (a.first == b.first) { return a.second < b.second; }
	else { return a.first < b.first; }
}

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);
	cout.tie(NULL);
	cout.sync_with_stdio(false);

	int N = 0;
	cin >> N;

	vector<pair<int, int>> coor = vector<pair<int, int>>(N);
	for (pair<int, int> &p : coor) {
		cin >> p.first >> p.second;
	}

	make_heap(coor.begin(), coor.end(), comp);
	sort_heap(coor.begin(), coor.end(), comp);

	for (pair<int, int> &p : coor) {
		cout << p.first << ' ' << p.second << '\n';
	}

	return 0;
}