#include <iostream>
using namespace std;

int main() {
	unsigned long long first = 0, second = 1;
	int N = 0;
	cin >> N;
	if (N == 0 || N == 1) {
		cout << N;
	}
	else {
		unsigned long long temp = 0;
		for (int i = 0; i < N - 1; i++) {
			temp = first + second;
			first = second;
			second = temp;
		}
		cout << second;
	}

	return 0;
}