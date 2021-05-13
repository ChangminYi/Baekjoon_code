#include <iostream>
#include <deque>
#include <vector>
using namespace std;

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);

	int num = 0;
	cin >> num;

	deque<int> original = deque<int>(num);
	deque<int> stk;
	for (int &i : original) {
		cin >> i;
	}

	int last = 0;
	while (last < num) {
		while (!original.empty() && original.front() != last + 1) {
			stk.push_back(original.front());
			original.pop_front();
		}
		if (!original.empty()) {
			last = original.front();
			original.pop_front();
		}

		while (!stk.empty() && stk.back() == last + 1) {
			last = stk.back();
			stk.pop_back();
		}

		for (int i = 0; stk.size() > 1 && i < stk.size() - 1; i++) {
			if (stk[i] < stk[i + 1]) {
				cout << "Sad";
				return 0;
			}
		}
	}

	cout << "Nice";

	return 0;
}