#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int A = 0, B = 0, C = 0;
	scanf("%d %d %d", &A, &B, &C);
	if (B < C) {
		printf("%d", A / (C - B) + 1);
	}
	else {
		puts("-1");
	}

	return 0;
}