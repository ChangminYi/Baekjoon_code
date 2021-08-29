#include <iostream>
#include <string>
using namespace std;

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);
	cout.tie(NULL);
	cout.sync_with_stdio(false);
	string s = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;'ZXCVBNM,./";
	string temp;

	while (getline(cin, temp)) {
		for (int i = 0; i < temp.size(); i++) {
			if (temp[i] == ' ') {
				continue;
			}
			else {
				for (int j = 0; j < s.length(); j++) {
					if (temp[i] == s[j]) {
						temp[i] = s[j - 1];
						break;
					}
				}
			}
		}
		cout << temp;
	}
	return 0;
}