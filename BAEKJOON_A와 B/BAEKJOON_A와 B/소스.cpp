#include <iostream>
#include <deque>
#include <queue>
#include <string>

using namespace std;

typedef struct NODE {
	deque<char> str;
	bool reverse;
}node;

bool comp(deque<char> &s1, string &s2, bool reverse) {
	if (s1.size() == s2.size()) {
		if (reverse) {
			for (uint32_t i = 0; i < s1.size(); i++) {
				if (s1[s1.size() - 1 - i] != s2[i]) { return false; }
			}
			return true;
		}
		else {
			for (uint32_t i = 0; i < s1.size(); i++) {
				if (s1[i] != s2[i]) { return false; }
			}
			return true;
		}
	}
	return false;
}

int canMake(string &toMake, string &origin) {
	deque<char> initStr(origin.size());
	for (uint32_t i = 0; i < initStr.size(); i++) {
		initStr[i] = origin[i];
	}

	queue<node> toCheck;
	toCheck.push({ initStr, false });
	while (!toCheck.empty()) {
		deque<char> curStr = toCheck.front().str;
		bool curReverse = toCheck.front().reverse;
		toCheck.pop();

		if (comp(curStr, toMake, curReverse)) {
			return 1;
		}
		else {
			if (curReverse) {
				if (curStr.front() == 'A') {
					deque<char> temp = curStr;
					temp.pop_front();
					if (temp.size() >= toMake.size()) {
						toCheck.push({ temp, curReverse });
					}
				}
				if (curStr.front() == 'B') {
					deque<char> temp = curStr;
					temp.pop_front();
					if (temp.size() >= toMake.size()) {
						toCheck.push({ temp, !curReverse });
					}
				}
			}
			else {
				if (curStr.back() == 'B') {
					deque<char> temp = curStr;
					temp.pop_back();
					if (temp.size() >= toMake.size()) {
						toCheck.push({ temp, !curReverse });
					}
				}
				if (curStr.back() == 'A') {
					deque<char> temp = curStr;
					temp.pop_back();
					if (temp.size() >= toMake.size()) {
						toCheck.push({ temp, curReverse });
					}
				}
			}
		}
	}

	return 0;
}

int main() {
	string s1, s2;
	cin >> s1 >> s2;

	cout << canMake(s1, s2);

	return 0;
}