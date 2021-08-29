#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <deque>

using namespace std;

unordered_map<string, bool> keyw;
int lasting;

deque<string> str_parse(string &str, char to_parse) {
	deque<string> ret;
	size_t base = 0, idx = 0;

	while ((idx = str.find_first_of(to_parse, idx)) != string::npos) {
		ret.push_back(str.substr(base, idx - base));
		idx += 1;
		base = idx;
	}
	ret.push_back(str.substr(base, idx - base));

	return ret;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	string temp;
	int m;
	cin >> lasting >> m;
	for (int i = 0; i < lasting; i++) {
		cin >> temp;
		keyw.insert(make_pair(temp, false));
	}
	for (int i = 0; i < m; i++) {
		cin >> temp;

		deque<string> prs = str_parse(temp, ',');
		for (string& str : prs) {
			if (keyw.find(str) != keyw.end() && keyw[str] == false) {
				keyw[str] = true;
				lasting--;
			}
		}

		cout << lasting << '\n';
	}

	return 0;
}