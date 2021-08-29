#include <iostream>
#include <deque>
#include <algorithm>
#include <set>

using namespace std;

typedef pair<int, int> pint;

bool cmp_pint(const pint& a, const pint& b) {
	if (a.second == b.second) {
		return a.first < b.first;
	}
	else {
		return a.second < b.second;
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	int n_chic, n_cow;
	cin >> n_chic >> n_cow;
	multiset<int> chic;
	deque<pint> cow = deque<pint>(n_cow);
	for (int i = 0, tmp; i < n_chic; i++) {
		cin >> tmp;
		chic.insert(tmp);
	}
	for (int i = 0; i < n_cow; i++) {
		cin >> cow[i].first >> cow[i].second;
	}
	sort(cow.begin(), cow.end(), cmp_pint);
	
	int match_count = 0;
	for (int i = 0; i < n_cow; i++) {
		multiset<int>::iterator s_res = chic.lower_bound(cow[i].first);

		if (s_res != chic.end() && *s_res <= cow[i].second) {
			match_count++;
			chic.erase(s_res);
		}
	}

	cout << match_count;

	return 0;
}