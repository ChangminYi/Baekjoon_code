#include <iostream>
using namespace std;

int main() {
	int N = 0, M = 0;
	cin >> N >> M;

	for (int i = 0, temp = M; i < 3; i++) {
		int ToMulti = temp % 10;
		temp /= 10;
		cout << N * ToMulti << '\n';
	}

	cout << N * M;

	return 0;
}