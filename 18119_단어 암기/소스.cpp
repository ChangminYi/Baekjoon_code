#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n = 0, m = 0;
	cin >> n >> m;

	string s;
	vector<int> words(n);
	for (int &i : words) {
		cin >> s;

		for (char &c : s) {
			i |= 1 << (c - 'a');
		}
	}

	int brain = 0x3ffffff;

	int inst = 0;
	char alp = 0;
	while (m--) {
		cin >> inst >> alp;

		if (inst == 1) {
			// forget
			brain &= ~(1 << (alp - 'a'));
		}
		else {
			// remember
			brain |= 1 << (alp - 'a');
		}


		int readable = 0;
		for (int &i : words) {
			if ((brain & i) == i) {
				readable++;
			}
		}
		cout << readable << '\n';
	}

	return 0;
}