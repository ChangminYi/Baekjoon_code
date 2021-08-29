#include <iostream>
using namespace std;

int main(void) {
	int N = 0, K = 0;
	cin >> N >> K;

	if (N <= K) {
		cout << 0;
	}
	else {
		int result = 0;
		for (result = 0; ; result++) {
			int count = 0, tempN = N;
			while (tempN != 0) {
				if (tempN % 2) {
					count++;
				}
				tempN /= 2;
			}

			if (count <= K) {
				break;
			}
			else {
				N++;
			}
		}
		cout << result;
	}
	return 0;
}
