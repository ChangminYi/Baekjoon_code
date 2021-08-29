#include <iostream>
#include <string>

using namespace std;

bool compare(string& ori, string& find, size_t idx) {
	for (size_t i = idx, j = 0; i < ori.size(); i++) {
		if (ori[i] == find[j]) {
			if (++j == find.size()) {
				return true;
			}
		}
		else {
			j = (ori[i] == find.front() ? 1 : 0);
		}
	}
	return false;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	string origin, tofind;
	cin >> origin >> tofind;

	string res;
	for (size_t i = 0; i < origin.size(); i++) {
		res.push_back(origin[i]);

		if (res.back() == tofind.back() && res.size() >= tofind.size()) {
			if (compare(res, tofind, res.size()-tofind.size())) {
				for (size_t j = 0; j < tofind.size(); j++) {
					res.pop_back();
				}
			}
		}
	}

	cout << (res.empty() ? "FRULA" : res);

	return 0;
}