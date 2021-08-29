#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	string s, res;
	stack<char> stk;
	getline(cin, s);

	for (uint32_t i = 0; i < s.size(); i++) {
		if (s[i] == '(') {
			stk.push(s[i]);
		}
		else if (s[i] == ')') {
			while (!stk.empty() && stk.top() != '(') {
				res.push_back(stk.top());
				stk.pop();
			}
			stk.pop();
		}
		else if (s[i] == '*' || s[i] == '/') {
			while (!stk.empty() && (stk.top() == '*' || stk.top() == '/')) {
				res.push_back(stk.top());
				stk.pop();
			}
			stk.push(s[i]);
		}
		else if (s[i] == '+' || s[i] == '-') {
			while (!stk.empty() && stk.top() != '(') {
				res.push_back(stk.top());
				stk.pop();
			}
			stk.push(s[i]);
		}
		else {
			res.push_back(s[i]);
		}
	}

	while (!stk.empty()) {
		res.push_back(stk.top());
		stk.pop();
	}

	cout << res;

	return 0;
}