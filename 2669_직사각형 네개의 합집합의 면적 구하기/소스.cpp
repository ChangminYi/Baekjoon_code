#include <iostream>
using namespace std;
#define SIZE 101

bool argb[SIZE][SIZE];

int main() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			argb[i][j] = false;
		}
	}

	for (int k = 0; k < 4; k++) {
		int coor[4];
		for (int i = 0; i < 4; i++) {
			cin >> coor[i];
		}

		for (int i = coor[0]; i < coor[2]; i++) {
			for (int j = coor[1]; j < coor[3]; j++) {
				argb[i][j] = true;
			}
		}
	}

	int count = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (argb[i][j]) { count++; }
		}
	}
	cout << count;

	return 0;
}