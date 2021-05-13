#include <iostream>
using namespace std;

int main() {
	int N = 0, count = 1;
	cin >> N;

	for (int temp = N;;) {
		temp = (temp % 10) * 10 + (temp % 10 + temp / 10) % 10;
		if (temp == N) {
			cout << count;
			break;
		}
		else { 
			count++;
		}
	}

	return 0;
}