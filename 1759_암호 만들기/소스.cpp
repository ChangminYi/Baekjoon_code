#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_set>

using namespace std;

#define ALPHABET 26


int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);
	
	int L = 0, C = 0;
	cin >> L >> C;
	vector<char> used(C);
	vector<bool> comb(C, false);
	unordered_set<char> vowel = { 'a', 'e', 'i', 'o', 'u' };
	for (char& c : used) {
		cin >> c;
	}
	for (int i = 0; i < L; i++) {
		comb[i] = true;
	}
	sort(used.begin(), used.end());

	string temp;
	do {
		int vowel_count = 0;

		for (uint32_t i = 0; i < comb.size(); i++) {
			if (comb[i]) {
				temp += used[i];

				if (vowel.find(used[i]) != vowel.end()) {
					vowel_count++;
				}
			}
		}

		if (vowel_count >= 1 && (temp.length() - vowel_count) >= 2) {
			cout << temp << '\n';
		}

		temp.clear();

	} while (prev_permutation(comb.begin(), comb.end()));

	return 0;
}