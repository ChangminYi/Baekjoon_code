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
		�� ����� ����23��:
			1. i������ �ִ� + (i+1)��° + (i+3)��°
			2. i������ �ִ� + (i+2��°)

		�׸��� 2ĭ�� �ǳʶٴ� ��찡 �ֱ� ������
			stack[i-1]�� stack[i]�� �񱳰� �ʿ�
		*/
		stack[i] = getMax(stack[i - 1], getMax(stack[i - 3] + argi[i - 1] + argi[i], stack[i - 2] + argi[i]));
		max = getMax(max, stack[i]);
	}

	cout << max;

	return 0;
}