#include <iostream>

int main() {
	int score[2][9] = { 0 }, s_temp[2][9] = { 0 };
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 9; j++) {
			std::cin >> score[i][j];
		}
	}

	s_temp[0][0] = score[0][0];
	s_temp[1][0] = score[1][0];
	for (int i = 0; i < 2; i++) {
		for (int j = 1; j < 9; j++) {
			s_temp[i][j] = s_temp[i][j - 1] + score[i][j];
		}
	}

	int winning = 0, losing = 0;
	if (s_temp[0][0] != 0) {
		winning = 1;
	}
	for (int i = 1; i < 9; i++) {
		if (s_temp[0][i] > s_temp[1][i - 1]) {
			winning = i;
		}
		if (s_temp[0][i] < s_temp[1][i]) {
			losing = i;
		}
	}

	std::cout << ((winning != 0 && winning <= losing) ? "Yes" : "No");

	system("pause");
	return 0;
}