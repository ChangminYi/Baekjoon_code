#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <queue>

using namespace std;

set<int> prime = {2, 3};

int inRange(int n) {
	if (1000 <= n && n <= 9999) {
		return true;
	}
	return false;
}

vector<int> make_possible(int n) {
	vector<int> ret;
	int origin = n;
	int dig[4];
	for (int i = 3; i >= 0; i--) {
		dig[i] = origin % 10;
		origin /= 10;
	}
	for (int i = 0; i < 4; i++) {
		int base = 0;

		for (int j = 0; j < 4; j++) {
			if (i != j) {
				base += dig[j] * pow(10, 3 - j);
			}
		}

		for (int j = 0, temp; j < 10; j++) {
			temp = base + j * pow(10, 3 - i);

			if (inRange(temp) && prime.find(temp) != prime.end() && temp != n) {
				ret.push_back(temp);
			}
		}
	}
	return ret;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	for (int i = 5; i <= 10000; i += 2) {
		bool divi = false;
		for (set<int>::iterator j = prime.begin(); (*j) <= sqrt(i); j++) {
			if (i % (*j) == 0) {
				divi = true;
				break;
			}
		}
		if (!divi) {
			prime.insert(i);
		}
	}

	int n;
	cin >> n;

	while (n-- > 0) {
		vector<bool> visit(10000, false);

		int frt, bak;
		int cnt = 0;
		bool can_convert = false;
		queue<pair<int, int>> que;
		cin >> frt >> bak;

		que.push(make_pair(frt, 0));
		visit[frt] = true;
		while (!que.empty()) {
			int cur = que.front().first;
			int cur_t = que.front().second;
			que.pop();

			if (cur == bak) {
				can_convert = true;
				cnt = cur_t;
				break;
			}
			else {
				vector<int> pos = make_possible(cur);
				for (int& i : pos) {
					if (!visit[i]) {
						visit[i] = true;
						que.push(make_pair(i, cur_t + 1));
					}
				}
			}
		}

		if (can_convert) {
			cout << cnt << '\n';
		}
		else {
			cout << "Impossible" << '\n';
		}
	}
	return 0;
}