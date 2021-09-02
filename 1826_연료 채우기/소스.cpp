#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> pint;

int n, endpoint, max_dist;
vector<pint> dat;
priority_queue<int> pq;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	dat.resize(n);
	for (pint& p : dat) {
		cin >> p.first >> p.second;
	}
	cin >> endpoint >> max_dist;
	sort(dat.begin(), dat.end());

	int fuel_count = 0;
	int idx = 0;
	bool cannot_reach = false;
	while (max_dist < endpoint) {
		while (idx < n && max_dist >= dat[idx].first) {
			pq.push(dat[idx++].second);
		}
		
		if (pq.empty()) {
			cannot_reach = true;
			break;
		}
		else {
			max_dist += pq.top();
			pq.pop();
			fuel_count++;
		}
	}

	cout << (cannot_reach ? -1 : fuel_count);

	return 0;
}