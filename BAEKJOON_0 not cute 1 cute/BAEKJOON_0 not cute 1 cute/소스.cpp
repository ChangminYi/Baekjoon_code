#include <iostream>

using namespace std;

int main() {
	int count = 0, leng = 0;
	int temp = 0;

	cin >> leng;

	for (int i = 0; i < leng; i++) {
		cin >> temp;

		if (temp == 0) {
			count++;
		}
	}


	cout << ((leng / 2) < count ? "Junhee is not cute!" : "Junhee is cute!");

	return 0;
}