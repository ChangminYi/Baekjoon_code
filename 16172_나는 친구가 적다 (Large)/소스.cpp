#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

string str_w_num;
string str_n_num;
string to_find;

vector<int> get_pi(const string &s) {
	vector<int> ret(s.length(), 0);

	for (int i = 1, j = 0; i < (int)s.length(); i++) {
		while (j > 0 && ret[i] != ret[j]) {
			j = ret[j - 1];
		}

		if (ret[i] == ret[j]) {
			j++;
			ret[i] = j;
		}
	}

	return ret;
}

bool kmp_search(const string& origin, const string& to_search) {
	vector<int> pi = get_pi(to_search);

	for (int i = 0, j = 0; i < (int)origin.length(); i++) {
		while (j > 0 && origin[i] != to_search[j]) {
			j = pi[j - 1];
		}

		if (origin[i] == to_search[j]) {
			if (j == (int)to_search.length() - 1) {
				return true;
			}
			else {
				j++;
			}
		}
	}

	return false;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> str_w_num;
	cin >> to_find;

	for (char& c : str_w_num) {
		if (isalpha(c)) {
			str_n_num.push_back(c);
		}
	}

	cout << (kmp_search(str_n_num, to_find) ? 1 : 0);

	return 0;
}