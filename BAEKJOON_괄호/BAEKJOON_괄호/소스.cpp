#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);
	int size = 0;
	cin >> size;
	for (; size > 0; size--) {
		stack<char> stk;
		string lang;
		cin >> lang;

		for (int i = 0; i < lang.size(); i++) {
			if (lang[i] == '(') {
				stk.push('(');
			}
			else if (lang[i] == ')') {
				if (stk.empty()) {
					cout << "NO\n";
					break;
				}
				else {
					stk.pop();
				}
			}

			if (i == lang.size() - 1) {
				if (stk.empty()) { cout << "YES\n"; }
				else { cout << "NO\n"; }
			}
		}
	}
	return 0;
}