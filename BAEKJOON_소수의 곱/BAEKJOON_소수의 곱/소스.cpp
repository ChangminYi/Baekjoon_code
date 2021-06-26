#include <iostream>
#include <queue>
#include <set>
#include <algorithm>
#include <functional>

using namespace std;
typedef long long lli;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	priority_queue<lli, vector<lli>, greater<lli>> pq;
	unsigned int n_prime, index;
	cin >> n_prime >> index;

	vector<lli> prime(n_prime);
	set<lli> same;
	for (lli& i : prime) {
		cin >> i;
	}

	lli pq_max = 0;
	pq.push(1);
	for (unsigned int i = 0; i < index; i++) {
		lli cur = pq.top();
		pq.pop();

		for (lli& j : prime) {
			lli nxt = j * cur;

			if (pq.size() <= index || nxt <= pq_max) {
				if (same.find(nxt) == same.end()) {
					same.insert(nxt);
					pq.push(nxt);
					pq_max = max(pq_max, nxt);
				}
			}
		}
	}

	cout << pq.top();

	return 0;
}