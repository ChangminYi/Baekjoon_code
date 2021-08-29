#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool isSame(const vector<vector<int>> &a, const vector<vector<int>> &b) {
	for (uint32_t i = 0; i < a.size(); i++) {
		for (uint32_t j = 0; j < a[i].size(); j++) {
			if (a[i][j] != b[i][j]) { return false; }
		}
	}
	return true;
}

vector<vector<int>> getCount(const string &s) {
	vector<vector<int>> count = vector<vector<int>>(2, vector<int>(26, 0));
	for (uint32_t i = 0; i < s.size(); i++) {
		if (islower(s[i])) {
			count[0][s[i] - 'a']++;
		}
		else {
			count[1][s[i] - 'A']++;
		}
	}
	return count;
}

void setCount(vector<vector<int>> &count, char toErase, char toAdd) {
	if (islower(toErase)) {
		count[0][toErase - 'a']--;
	}
	else {
		count[1][toErase - 'A']--;
	}
	if (islower(toAdd)) {
		count[0][toAdd - 'a']++;
	}
	else {
		count[1][toAdd - 'A']++;
	}
}

int main() {
	cin.tie(nullptr); cin.sync_with_stdio(false);
	cout.tie(nullptr); cout.sync_with_stdio(false);

	int n_g = 0, n_S = 0;
	cin >> n_g >> n_S;

	string g, S;
	cin >> g >> S;

	vector<vector<int>> g_count = getCount(g);
	vector<vector<int>> S_count = getCount(S.substr(0, n_g));
	int count = 0;
	int index = 0;
	do {
		if (isSame(g_count, S_count)) { count++; }
		if (index + n_g < n_S) {
			setCount(S_count, S[index], S[index + n_g]);
			index++;
		}
		else {
			break;
		}
	} while (true);

	cout << count;

	return 0;
}