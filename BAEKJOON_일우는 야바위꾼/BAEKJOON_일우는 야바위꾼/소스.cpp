#include <iostream>
using namespace std;

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);

	int N, X, K;
	cin >> N >> X >> K;
	for (int i = 0, temp[2]; i < K; i++) {
		cin >> temp[0] >> temp[1];
		if (X == temp[0]) {
			X = temp[1];
		}
		else if (X == temp[1]) {
			X = temp[0];
		}
	}

	cout << X;

	return 0;
}