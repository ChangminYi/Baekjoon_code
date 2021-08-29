#include <iostream>
#include <string>
#include <vector>

using namespace std;

unsigned int find(const string &s, const char tofind) {
	unsigned int count = 0;
	for (uint32_t i = 0; i < s.size(); i++) {
		if (s[i] == tofind) { count++; }
	}
	return count;
}

unsigned int find(const string &s, const string tofind) {
	for (uint32_t i = 0; i < s.size() - tofind.size() + 1; i++) {
		if (s.substr(i, tofind.size()) == tofind) {
			return i;
		}
	}
	return s.size();
}

unsigned int getfirstindex(const string &s, const int start, const char tofind) {
	for (int i = start; i < s.size(); i++) {
		if (s[i] == tofind) { return i; }
	}
	return s.size();
}

int main() {
	string in;
	cin >> in;

	int colonNum = find(in, ':');
	vector<string> parse;
	if (colonNum == 7) {
		for (uint32_t i = 0, left = 0; i < 8; i++) {
			int right = getfirstindex(in, left, ':');
			parse.push_back(in.substr(left, right - left));
			left = right + 1;
		}
	}
	else {
		string first, second;
		int ind = find(in, "::");
		first = in.substr(0, ind);
		second = in.substr(ind + 2, in.size());

		int count = find(first, ':') + find(second, ':');
		for (uint32_t i = 0, left = 0; i < find(first, ':') + 1; i++) {
			int right = getfirstindex(first, left, ':');
			string temp = first.substr(left, right - left);
			if (!temp.empty()) {
				parse.push_back(first.substr(left, right - left));
			}
			else {
				parse.push_back("0000");
			}
			left = right + 1;
		}
		for (uint32_t i = 0; i < 6 - count; i++) {
			parse.push_back("0000");
		}
		for (uint32_t i = 0, left = 0; i < find(second, ':') + 1; i++) {
			int right = getfirstindex(second, left, ':');
			parse.push_back(second.substr(left, right - left));
			left = right + 1;
		}
	}

	for (uint32_t i = 0; i < parse.size(); i++) {
		for (uint32_t j = 0; j < 4 - parse[i].size(); j++) {
			cout << 0;
		}
		cout << parse[i];
		if (i < parse.size() - 1) {
			cout << ':';
		}
	}

	return 0;
}