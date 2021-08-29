#include <iostream>

using namespace std;

int getMax(int a, int b) {
	return (a > b ? a : b);
}

int main() {
	int length = 0, max = 0;
	int argi[10003] = { 0 }, stack[10003] = { 0 };

	cin >> length;

	for (int i = 3; i < length + 3; i++) {
		cin >> argi[i];
	}

	for (int i = 3; i < length + 3; i++) {
		/*
		총 경우의 수는23개:
			1. i까지의 최댓값 + (i+1)번째 + (i+3)번째
			2. i까지의 최댓값 + (i+2번째)

		그리고 2칸을 건너뛰는 경우가 있기 때문에
			stack[i-1]과 stack[i]의 비교가 필요
		*/
		stack[i] = getMax(stack[i - 1], getMax(stack[i - 3] + argi[i - 1] + argi[i], stack[i - 2] + argi[i]));
		max = getMax(max, stack[i]);
	}

	cout << max;

	return 0;
}