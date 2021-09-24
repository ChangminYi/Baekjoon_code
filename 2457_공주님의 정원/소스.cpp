#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> pint;

constexpr int START = 301;
constexpr int END = 1201;

int n;
vector<pint> argi;

int conv_date(int month, int day) {
	return month * 100 + day;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	argi.resize(n);
	for (int i = 0, s1, s2, e1, e2; i < n; i++) {
		cin >> s1 >> s2 >> e1 >> e2;

		if (s1 * 100 + s2 < START) {
			s1 = 3;
			s2 = 1;
		}
		if (e1 * 100 + e2 >= END) {
			e1 = 12;
			e2 = 01;
		}

		argi[i] = pint(conv_date(s1, s2), conv_date(e1, e2));
	}

	sort(argi.begin(), argi.end());

	int start = 300;
	int end = 301;
	int res = 0;
	for (int i = 0, max_end = 0, max_idx; i < n; i++) {
		if (start < argi[i].first && argi[i].first <= end) {
			if (max_end < argi[i].second) {
				max_end = argi[i].second;
				max_idx = i;
			}
			if (argi[i].second == END) {
				res++;
				end = max_end;
				break;
			}
		}
		else {
			if (end >= max_end) {
				break;
			}
			else {
				start = end;
				end = max_end;
				res++;
				i--;
			}
		}
	}

	cout << (end == 1201 ? res : 0);

	return 0;
}