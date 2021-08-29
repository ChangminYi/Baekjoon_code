#include <iostream>
#include <cstdio>

int main() {
	int size = 0;
	std::cin >> size;

	for (int i = 1; i < size; i++) {
		printf("%d\n", i);
	}
	printf("%d", size);

	return 0;
}