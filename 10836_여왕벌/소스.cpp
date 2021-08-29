//규칙찾기: 0번째 열의 출력 방식만 다름
//0번째 열은 argi(0, argiSize-1)까지의 범위를 역순으로 출력
//나머지 열은 해당 열의 첫번째 행의 값과 모두 같음

#include <iostream>
#include <vector>
using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int argSize = 0, day = 0;
	cin >> argSize >> day;

	vector<int> argi = vector<int>(argSize * 2 - 1, 1);
	for (int i = 0; i < day; i++) {
		int temp[3];
		cin >> temp[0] >> temp[1] >> temp[2];

		for (int j = temp[0]; j < temp[0] + temp[1]; j++) { argi[j] += 1; }
		for (int j = temp[0] + temp[1]; j < temp[0] + temp[1] + temp[2]; j++) { argi[j] += 2; }
	}

	for (int i = 0; i < argSize; i++) {
		for (int j = 0; j < argSize; j++) {
			if (j == 0) {
				cout << argi[argSize - 1 - i] << ' ';
			}
			else {
				cout << argi[argSize - 1 + j] << ' ';
			}
		}
		cout << '\n';
	}

	return 0;
}