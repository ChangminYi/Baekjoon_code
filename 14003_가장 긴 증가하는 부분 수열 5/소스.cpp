#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n;
	cin >> n;

	vector<int> argi(n);
	vector<int> idx(n);
	for (int& i : argi) {
		cin >> i;
	}

	int counter = 0;
	vector<int> sequence;
	sequence.push_back(argi.front());
	for (int i = 1; i < n; i++) {
		if (sequence.back() < argi[i]) {
			sequence.push_back(argi[i]);
			idx[i] = ++counter;
		}
		else {
			vector<int>::iterator lb = lower_bound(sequence.begin(), sequence.end(), argi[i]);
			int tmp_idx = distance(sequence.begin(), lb);
			sequence[tmp_idx] = argi[i];
			idx[i] = tmp_idx;
		}
	}

	stack<int> to_print;
	for (int i = n - 1; i >= 0 && counter >= 0; i--) {
		if (idx[i] == counter) {
			to_print.push(argi[i]);
			counter--;
		}
	}

	cout << sequence.size() << '\n';
	while (!to_print.empty()) {
		cout << to_print.top() << ' ';
		to_print.pop();
	}

	return 0;
}