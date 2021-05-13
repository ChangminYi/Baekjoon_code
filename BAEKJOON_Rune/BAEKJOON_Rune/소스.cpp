#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef class RUNE {
public:
	string st;
	int power;
	RUNE() {}
	RUNE(string &s) :st(s), power(_getPower(s)) {}
	bool operator<(RUNE &r) {
		if (this->power == r.power) { return this->st < r.st; }
		else { return this->power > r.power; }
	}
private:
	bool _isVowel(char c) {
		switch (c) {
		case 'a':
		case 'e':
		case 'i':
		case 'o':
		case 'u': return true;
		default: return false;
		}
	}
	vector<int> _getAllVowel(string &s) {
		vector<int> index;
		for (int i = 0; i < s.size(); i++) {
			if (_isVowel(s[i])) {
				index.push_back(i);
			}
		}
		return index;
	}
	int _getPower(string &s) {
		int count = 0;
		int adj = -2;
		vector<int> vowel = _getAllVowel(s);
		if (vowel.empty()) {
			return 0;
		}
		else {
			for (int i : vowel) {
				if (adj + 1 != i) {
					count++;
				}
				adj = i;
			}
		}
		return count;
	}
}rune;

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);
	cout.tie(NULL);
	cout.sync_with_stdio(false);

	int num = 0;
	cin >> num;
	for (; num > 0; num--) {
		int iter = 0;
		cin >> iter;
		vector<rune> args;
		for (int i = 0; i < iter; i++) {
			string temp;
			cin >> temp;
			args.push_back(rune(temp));
		}
		sort(args.begin(), args.end());

		for (int i = 0; i < iter; i++) {
			cout << args[i].st;
			if (i != iter - 1) { cout << ' '; }
			else { cout << '\n'; }
		}
	}
	return 0;
}