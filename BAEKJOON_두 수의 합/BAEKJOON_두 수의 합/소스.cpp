#include <iostream>

using namespace std;

bool arr[10000001] = { false };

int main() {
	cin.tie(nullptr); cin.sync_with_stdio(false);
	cout.tie(nullptr); cout.sync_with_stdio(false);
	
	int N = 0;
	cin >> N;
	for (int i = 0, temp = 0; i < N; i++) {
		cin >> temp;
		arr[temp] = true;
	}

	int X = 0;
	cin >> X;
	int range = X / 2;
	if (X % 2 == 0) { range--; }

	int count = 0;
	for (int i = 1; i <= range; i++) {
		if (arr[i] && arr[X - i]) {
			count++;
		}
	}

	cout << count;

	return 0;
}