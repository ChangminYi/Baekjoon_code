#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> get_Pi(string& s) {
	vector<int> ret(s.length(), 0);
	for (size_t i = 1, j = 0; i < s.length(); i++) {
		while (0 < j && s[i] != s[j]) {
			j = ret[j - 1];
		}
		if (s[i] == s[j]) {
			ret[i] = ++j;
		}
	}
	return ret;
}

int kmp_search(string& small, string& origin) {
	vector<int> Pi = get_Pi(small);

	for (size_t i = 0, j = 0; i < origin.length(); i++) {
		while (0 < j && origin[i] != small[j]) {
			j = Pi[j - 1];
		}
		if (origin[i] == small[j]) {
			if (j == small.length() - 1) {
				return 1;
			}
			else {
				j++;
			}
		}
	}

	return 0;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	string origin, to_find;
	cin >> origin >> to_find;

	cout << kmp_search(to_find, origin);

	return 0;
}