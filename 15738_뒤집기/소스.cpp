#include <iostream>
using namespace std;

bool isInScope(int index, int min, int max) {
	return ((min <= index) && (index <= max));
}

int switchIndex(int index, int min, int max) {
	return (max + min) - index;
}

int main() {
	int arrSize = 0;
	int toFindIndex = 0;
	int calculateSize = 0;

	cin >> arrSize >> toFindIndex >> calculateSize;
	for (int i = 0, temp = 0; i < arrSize; i++) {
		cin >> temp;
	}
	for (int i = 0, calculate = 0; i < calculateSize; i++) {
		cin >> calculate;

		if (calculate < 0) {
			if (isInScope(toFindIndex, arrSize + calculate + 1, arrSize)) {
				toFindIndex = switchIndex(toFindIndex, arrSize + calculate + 1, arrSize);
			}
		}
		else {
			if (isInScope(toFindIndex, 1, calculate)) {
				toFindIndex = switchIndex(toFindIndex, 1, calculate);
			}
		}
	}

	cout << toFindIndex;

	return 0;
}