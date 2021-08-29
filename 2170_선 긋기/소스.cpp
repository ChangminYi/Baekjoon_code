#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

int n;
vector<pint> line;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	
	line.resize(n);
	for (pint& p : line) {
		cin >> p.first >> p.second;
	}

	sort(line.begin(), line.end());

	int len_sum = 0;
	int left = line[0].first;
	int right = line[0].second;
	for (int i = 1; i < n; i++) {
		if (right < line[i].first) {
			len_sum += right - left;

			left = line[i].first; 
			right = line[i].second;
		}
		else {
			right = max(right, line[i].second);
		}
	}
	len_sum += right - left;

	cout << len_sum;

	return 0;
}