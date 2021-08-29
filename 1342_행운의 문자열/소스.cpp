#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	string s;
	cin >> s;

	if (s.size() == 1) {
		cout << 1;
	}
	else if (s.size() == 2) {
		if (s.front() == s.back()) {
			cout << 0; 
		}
		else {
			cout << 2;
		}
	}
	else {
		int num = 0;
		sort(s.begin(), s.end());
		do {
			for (uint32_t i = 1; i < s.size() - 1; i++) {
				if (s[i - 1] == s[i] || s[i] == s[i + 1]) {
					break;
				}
				if (i == s.size() - 2) { num++; }
			}
		} while (next_permutation(s.begin(), s.end()));
		cout << num;
	}

	return 0;
}