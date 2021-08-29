#include <iostream>
#include <vector>
#include <string>

#define INF 0x7fffFFFF

using namespace std;

vector<bool> visit;

void print(int left, int right, string &str) {
	int tempMin = INF, idx = -1;
	for (int i = left; i <= right; i++) {
		if (!visit[i] && str[i] < tempMin) {
			tempMin = str[i];
			idx = i;
		}
	}

	if (tempMin != INF) {
		visit[idx] = true;
		for (int i = 0; str[i]; i++) {
			if (visit[i]) {
				cout << str[i];
			}
		}
		cout << '\n';

		print(idx + 1, right, str);
		print(left, idx - 1, str);
	}

	return;
}


int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	string s;
	cin >> s;
	visit.assign(s.size(), false);

	print(0, s.size() - 1, s);

	return 0;
}