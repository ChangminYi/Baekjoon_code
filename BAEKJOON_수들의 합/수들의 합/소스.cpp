#include <iostream>
using namespace std;

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);

	long long S = 0;
	long long sum = 0;
	int i = 0;

	cin >> S;

	do { sum += ++i; } while (sum <= S);

	cout << i - 1;

	return 0;
}
