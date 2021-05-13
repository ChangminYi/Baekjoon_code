#include <iostream>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int T = 0;
	cin >> T;
	for (int t = 0; t < T; t++) {
		multiset<int> st;
		int numInst = 0;
		cin >> numInst;
		for (int j = 0; j < numInst; j++) {
			string inst;
			int num = 0;
			cin >> inst >> num;

			if (inst == "I") {
				st.insert(num);
			}
			else if (inst == "D") {
				if (num == -1) {
					if (!st.empty()) {
						st.erase(st.begin());
					}
				}
				else {
					if (!st.empty()) {
						st.erase(--st.end());
					}
				}
			}
		}

		if (st.empty()) {
			cout << "EMPTY" << '\n';
		}
		else {
			cout << *(--st.end()) << ' ' << *st.begin() << '\n';
		}
	}

	return 0;
}