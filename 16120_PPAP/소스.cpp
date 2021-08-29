#include <iostream>
#include <deque>
#include <string>
#include <stack>

using namespace std;

bool is_same_sub(string& longer, string& to_cmp, int offset) {
	for (size_t i = 0; i < to_cmp.length(); i++) {
		if (longer[offset + i] != to_cmp[i]) {
			return false;
		}
	}
	return true;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	string ppap = "PPAP";
	string str;
	cin >> str;

	string seen;
	int idx = (int)ppap.length() * (-1);
	for (size_t i = 0; ;) {
		if (idx < 0 && i < str.length()) {
			seen.push_back(str[i]);
			idx++;
			i++;
		}
		else {
			if (is_same_sub(seen, ppap, idx)) {
				for (size_t j = 0; j < ppap.length(); j++) {
					seen.pop_back();
				}
				seen.push_back('P');
				idx -= ppap.length() - 1;

				if (seen.length() < ppap.length() && i == str.length()) {
					break;
				}
			}
			else {
				if (i < str.length()) {
					seen.push_back(str[i]);
					idx++;
					i++;
				}
				else {
					break;
				}
			}
		}
	}

	if (seen == "P") {
		cout << "PPAP";
	}
	else {
		cout << "NP";
	}

	return 0;
}