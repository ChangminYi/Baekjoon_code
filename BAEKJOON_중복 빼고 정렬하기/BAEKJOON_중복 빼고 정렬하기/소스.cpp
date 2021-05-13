#include <iostream>
#include <vector>
using namespace std;

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);
	cout.tie(NULL);
	cout.sync_with_stdio(false);

	int size = 0;
	cin >> size;
	vector<bool> count = vector<bool>(2001, false);
	for (int i = 0; i < size; i++) {
		int temp = 0;
		cin >> temp;
		count[temp + 1000] = true;
	}

	for (int i = 0; i < 2001; i++) {
		if (count[i]) { cout << i - 1000 << ' '; }
	}

	return 0;
}