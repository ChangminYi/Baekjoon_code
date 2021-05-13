#include <iostream>
#include <vector>
using namespace std;

vector<vector<char>> patt;

void drawPattern(int N) {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cout << patt[i][j];
		}
		cout << '\n';
	}
}

void makePattern(pair<int, int> upleft, pair<int, int> downright) {
	if (upleft.first + 2== downright.first && upleft.second + 2 == downright.second) {
		patt[upleft.first + 1][upleft.second + 1] = ' ';
		return;
	}
	else {
		int spaceLength = (downright.first - upleft.first + 1) / 3;
		for (int i = upleft.first + spaceLength; i < upleft.first + spaceLength * 2; i++) {
			for (int j = upleft.second + spaceLength; j < upleft.second + spaceLength * 2; j++) {
				patt[i][j] = ' ';
			}
		}

		makePattern({ upleft.first, upleft.second }, { upleft.first + spaceLength - 1, upleft.second + spaceLength - 1 });
		makePattern({ upleft.first, upleft.second + spaceLength }, { upleft.first + spaceLength - 1, upleft.second + 2 * spaceLength - 1 });
		makePattern({ upleft.first, upleft.second + 2 * spaceLength }, { upleft.first + spaceLength - 1, upleft.second + 3 * spaceLength - 1 });
		makePattern({ upleft.first + spaceLength, upleft.second }, { upleft.first + 2 * spaceLength - 1, upleft.second + spaceLength - 1 });
		makePattern({ upleft.first + spaceLength, upleft.second + 2 * spaceLength }, { upleft.first + 2 * spaceLength - 1, upleft.second + 3 * spaceLength - 1 });
		makePattern({ upleft.first + 2 * spaceLength, upleft.second }, { upleft.first + 3 * spaceLength - 1, upleft.second + spaceLength - 1 });
		makePattern({ upleft.first + 2 * spaceLength, upleft.second + spaceLength }, { upleft.first + 3 * spaceLength - 1, upleft.second + 2 * spaceLength - 1 });
		makePattern({ upleft.first + 2 * spaceLength, upleft.second + 2 * spaceLength }, { upleft.first + 3 * spaceLength - 1, upleft.second + 3 * spaceLength - 1 });
	}
}

int main() {
	int N = 0;
	cin >> N;
	patt = vector<vector<char>>(N + 1, vector<char>(N + 1, '*'));
	makePattern({ 1, 1 }, { N, N });
	drawPattern(N);
	return 0;
}