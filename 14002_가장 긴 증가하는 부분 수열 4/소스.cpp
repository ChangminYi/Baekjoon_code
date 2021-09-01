#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

int n;
vector<int> argi, idx, seq;
stack<int> stk;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	argi.resize(n);
	idx.resize(n);
	for (int& i : argi) {
		cin >> i;
	}

	int cnt = 0;
	seq.push_back(argi[0]);
	for (int i = 1; i < n; i++) {
		if (seq.back() < argi[i]) {
			seq.push_back(argi[i]);
			idx[i] = ++cnt;
		}
		else {
			auto lb = lower_bound(seq.begin(), seq.end(), argi[i]);
			*lb = argi[i];
			idx[i] = distance(seq.begin(), lb);
		}
	}

	for (int i = n - 1; i >= 0 && cnt >= 0; i--) {
		if (idx[i] == cnt) {
			cnt--;
			stk.push(argi[i]);
		}
	}

	cout << stk.size() << '\n';
	while (!stk.empty()) {
		cout << stk.top() << ' ';
		stk.pop();
	}

	return 0;
}