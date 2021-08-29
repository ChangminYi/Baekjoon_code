#include <iostream>
using namespace std;


int main() {
	int row = 0, col = 0;
	cin >> row >> col;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << '*';
		}

		if (i != row - 1) {
			cout << endl;
		}
	}

	return 0;
}