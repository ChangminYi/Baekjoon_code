#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int iter = 0;
	cin >> iter;

	stack<int> stk;
	vector<int> args(iter);
	vector<int> res(iter);
	for (int& i : args) {
		cin >> i;
	}

	for (int i = iter - 1; i >= 0; i--) {
		while (!stk.empty() && stk.top() <= args[i]) {
			stk.pop();
		}

		if (stk.empty()) {
			res[i] = -1;
		}
		else {
			res[i] = stk.top();
		}

		stk.push(args[i]);
	}

	for (int& i : res) {
		cout << i << ' ';
	}

	return 0;
}