#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <functional>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

int n;
vector<pint> timeline;
vector<int> use_count;
priority_queue<pint, vector<pint>, greater<pint>> pq;
set<int> useable_seat;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	timeline = vector<pint>(n);
	use_count = vector<int>(n);
	for (pint& p : timeline) {
		cin >> p.first >> p.second;
	}

	sort(timeline.begin(), timeline.end());
	int min_seat = 0;
	for (pint& p : timeline) {
		while (!pq.empty()) {
			if (pq.top().first <= p.first) {
				useable_seat.insert(pq.top().second);
				pq.pop();
			}
			else {
				break;
			}
		}

		if (useable_seat.empty()) {
			pq.push(make_pair(p.second, min_seat));
			use_count[min_seat]++;
			min_seat++;
		}
		else {
			int empty_seat = *useable_seat.begin();
			useable_seat.erase(useable_seat.begin());
			pq.push(make_pair(p.second, empty_seat));
			use_count[empty_seat]++;
		}
	}

	cout << min_seat << '\n';
	for (int i = 0; i < min_seat; i++) {
		cout << use_count[i] << ' ';
	}

	return 0;
}