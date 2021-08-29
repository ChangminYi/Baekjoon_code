#include <iostream>
#include <stack>
#include <string>
using namespace std;

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);
	cout.tie(NULL);
	cout.sync_with_stdio(false);

	int num = 0;
	stack<int> stk;
	cin >> num;
	for (int i = 0; i < num; i++) {
		string inst;
		cin >> inst;
		if (inst == "push") {
			int data = 0;
			cin >> data;
			stk.push(data);
		}
		else if (inst == "pop") {
			if (stk.empty()) {
				cout << -1;
			}
			else {
				cout << stk.top();
				stk.pop();
			}
			cout << '\n';
		}
		else if (inst == "size") {
			cout << stk.size() << '\n';
		}
		else if (inst == "empty") {
			if (stk.empty()) {
				cout << 1;
			}
			else {
				cout << 0;
			}
			cout << '\n';
		}
		else if (inst == "top") {
			if (stk.empty()) {
				cout << -1;
			}
			else {
				cout << stk.top();
			}
			cout << '\n';
		}
	}

	return 0;
}