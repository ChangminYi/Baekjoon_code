#include <iostream>

using namespace std;

int main() {
	char credit[17] = { 0 };
	char *output;
	int num;

	cin >> num;
	output = new char(num);
	for (int i = 0; i < num; i++) {
		cin >> credit;
		for (int j = 0; j < 16; j++) {
			credit[j] -= '0';
		}

		for (int j = 0; j < 8; j++) {
			credit[2 * j] *= 2;
			if (credit[2 * j] >= 10) {
				credit[2 * j] = (credit[2 * j] / 10) + (credit[2 * j] % 10);
			}
		}

		int tmp = 0;
		for (int j = 0; j < 16; j++) {
			tmp += credit[j];
		}

		output[i] = (tmp % 10 == 0) ? 'T' : 'F'; 
	}

	for (int i = 0; i < num; i++) {
		cout << output[i] << endl;
	}

	system("pause");
	return 0;
}