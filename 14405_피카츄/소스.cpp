#include <iostream>
#include <string>
using namespace std;

bool isSameWith(string tofind, string &tosearch, int index) {
	if (tofind.size() > tosearch.size()) { return false; }
	else {
		for (int i = 0; i < tofind.size(); i++) {
			if (tofind[i] != tosearch[index + i]) { return false; }
		}
	}
	return true;
}

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);

	string str;
	cin >> str;

	for (int i = 0; i < str.size();) {
		if (isSameWith("pi", str, i) || isSameWith("ka", str, i)) { i += 2; }
		else if (isSameWith("chu", str, i)) { i += 3; }
		else {
			cout << "NO";
			return 0;
		}
	}

	cout << "YES";

	return 0;
}