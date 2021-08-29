//��Ģã��: 0��° ���� ��� ��ĸ� �ٸ�
//0��° ���� argi(0, argiSize-1)������ ������ �������� ���
//������ ���� �ش� ���� ù��° ���� ���� ��� ����

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