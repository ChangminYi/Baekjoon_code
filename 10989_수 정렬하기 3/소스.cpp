#include <iostream>
using namespace std;

int argi[100001] = { 0 };
int leng = 0;

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);

	cin >> leng;
	for (int i = 0, temp = 0; i < leng; i++) {
		cin >> temp;
		argi[temp]++;
	}

	for (int i = 1; i < 10001; i++) {
		if (argi[i]) {
			for (int j = 0; j < argi[i]; j++) {
				cout << i << '\n';
			}
		}
	}

	return 0;
}