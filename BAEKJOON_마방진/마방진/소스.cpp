//틀림ㅜ

//8 1 6
//3 5 7
//4 9 2

#include <iostream>
using namespace std;

int getDist(int a, int b) {
	return b - a;
}

void printArgi(int **argi) {
	cout << argi[0][0] << ' ' << argi[0][1] << ' ' << argi[0][2] << endl;
	cout << argi[1][0] << ' ' << argi[1][1] << ' ' << argi[1][2] << endl;
	cout << argi[2][0] << ' ' << argi[2][1] << ' ' << argi[2][2];
}

int main() {
	int **argi = new int*[3];
	for (int i = 0; i < 3; i++) {
		argi[i] = new int[3];
	}
	int dist = 0;

	for (int i = 0; i < 3; i++) {
		cin >> argi[i][0] >> argi[i][1] >> argi[i][2];
	}

	if (argi[0][1] != 0 && argi[2][2] != 0) {
		dist = getDist(argi[0][1], argi[2][2]);
	}
	else if (argi[2][2] != 0 && argi[1][0]) {
		dist = getDist(argi[2][2], argi[1][0]);
	}//3과 4는 건너뜀
	else if (argi[2][0] != 0 && argi[1][1] != 0) {
		dist = getDist(argi[2][0], argi[1][1]);
	}
	else if (argi[1][1] != 0 && argi[0][2] != 0) {
		dist = getDist(argi[1][1], argi[0][2]);
	}//6과 7은 건너뜀
	else if (argi[1][2] != 0 && argi[0][0] != 0) {
		dist = getDist(argi[1][2], argi[0][0]);
	}
	else if (argi[0][0] != 0 && argi[2][1] != 0) {
		dist = getDist(argi[0][0], argi[2][1]);
	}

	while (true) {
		if (argi[0][1] == 0) {	//1
			if (argi[2][2] != 0) {
				argi[0][1] = argi[2][2] - dist;
			}
			else if (argi[1][0] != 0) {
				argi[0][1] = argi[1][0] - 2 * dist;
			}
		}
		else if (argi[2][2] == 0) {	//2
			if (argi[0][1] != 0) {
				argi[2][2] = argi[0][1] + dist;
			}
			else if (argi[1][0] != 0) {
				argi[2][2] = argi[1][0] - dist;
			}
		}
		else if (argi[1][0] == 0) {	//3
			if (argi[0][1] != 0) {
				argi[1][0] = argi[0][1] + 2 * dist;
			}
			else if (argi[2][2] != 0) {
				argi[1][0] = argi[2][2] + dist;
			}
		}
		else if (argi[2][0] == 0) {	//4
			if (argi[1][1] != 0) {
				argi[2][0] = argi[1][1] - dist;
			}
			else if (argi[0][2] != 0) {
				argi[2][0] = argi[0][2] - 2 * dist;
			}
		}
		else if (argi[1][1] == 0) {	//5
			if (argi[2][0] != 0) {
				argi[1][1] = argi[2][0] + dist;
			}
			else if (argi[0][2] != 0) {
				argi[1][1] = argi[0][2] - dist;
			}
		}
		else if (argi[0][2] == 0) {	//6
			if (argi[2][0] != 0) {
				argi[0][2] = argi[1][1] + 2 * dist;
			}
			else if (argi[1][1] != 0) {
				argi[0][2] = argi[1][1] + dist;
			}
		}
		else if (argi[1][2] == 0) {	//7
			if (argi[0][0] != 0) {
				argi[1][2] = argi[0][0] - dist;
			}
			else if (argi[2][1] != 0) {
				argi[1][2] = argi[2][1] - 2 * dist;
			}
		}
		else if (argi[0][0] == 0) {	//8
			if (argi[1][2] != 0) {
				argi[0][0] = argi[1][2] + dist;
			}
			else if (argi[2][1] != 0) {
				argi[0][0] = argi[2][1] - dist;
			}
		}
		else if (argi[2][1] == 0) {	//9
			if (argi[1][2] != 0) {
				argi[2][1] = argi[1][2] + 2 * dist;
			}
			else if (argi[0][0] != 0) {
				argi[2][1] = argi[0][0] + dist;
			}
		}
		else {
			break;
		}
	}

	printArgi(argi);

	for (int i = 0; i < 3; i++) {
		delete[] argi[i];
	}
	delete[] argi;
	return 0;
}