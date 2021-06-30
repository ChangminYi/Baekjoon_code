#include <iostream>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int tm;
	cin >> tm;
	int to_div[3] = { 300, 60, 10 };
	int cnt[3] = { 0, 0, 0 };
	for (int i = 0; i < 3; i++) {
		while (tm >= to_div[i]) {
			tm -= to_div[i];
			cnt[i]++;
		}
	}

	if (tm != 0) {
		cout << -1;
	}
	else {
		for (int i = 0; i < 3; i++) {
			cout << cnt[i] << ' ';
		}
	}

	return 0;
}