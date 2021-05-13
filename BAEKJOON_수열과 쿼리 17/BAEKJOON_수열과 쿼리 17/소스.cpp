//뭔가 다른 자료구조가 있음

#include <iostream>
using namespace std;

int main() {
	cin.tie(NULL);
	cout.tie(NULL);
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);

	int num;
	int argi[100001];
	cin >> num;
	for (int i = 1; i <= num; i++) {
		cin >> argi[i];
	}

	int queryNum = 0;
	cin >> queryNum;
	for (int i = 0, temp[3]; i < queryNum; i++) {
		cin >> temp[0] >> temp[1] >> temp[2];

		if (temp[0] == 2) {
			int min = argi[temp[1]];
			for (int j = temp[1] + 1; j <= temp[2]; j++) {
				if (argi[j] < min) { min = argi[j]; }
			}
			cout << min << '\n';
		}
		else {
			argi[temp[1]] = temp[2];
			continue;
		}
	}

	return 0;
}