#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> getPi(string s) {
	vector<int> pi(s.size(), 0);

	for (int i = 1, j = 0; i < s.size(); i++) {
		while ((j > 0) && (s[i] != s[j])) {
			j = pi[j - 1];
		}
		if (s[i] == s[j]) {
			pi[i] = ++j;
		}
	}

	return pi;
}

vector<uint32_t> kmp_search(string toFind, string set) {
	vector<uint32_t> ans;
	vector<int> pi = getPi(toFind);

	for (int i = 0, j = 0, m = toFind.size(); i < set.size(); i++) {
		while (j > 0 && set[i] != toFind[j]) {
			j = pi[j - 1];
		}
		if (set[i] == toFind[j]) {
			if (j == m - 1) {
				ans.push_back(i - m + 1);
				j = pi[j];
			}
			else {
				j++;
			}
		}
	}

	return ans;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	string N, M;
	getline(cin, N);
	getline(cin, M);

	vector<uint32_t> index = kmp_search(M, N);

	cout << index.size() << '\n';
	for (uint32_t i = 0; i < index.size(); i++) {
		cout << index[i] + 1 << ' ';
	}

	return 0;
}