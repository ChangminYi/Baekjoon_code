#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

int main() {
	double *lowest = new double[7 + 1];
	int num = 0;
	cin >> num;

	for (int i = 0; i < 7; i++) {
		cin >> lowest[i];
	}
	for (int i = 0; i < num - 7; i++) {
		cin >> lowest[7];
		sort(lowest, lowest + 8);
	}

	for (int i = 0; i < 7; i++) {
		printf("%.3lf\n", lowest[i]);
	}

	delete[] lowest;
	system("pause");
	return 0;
}