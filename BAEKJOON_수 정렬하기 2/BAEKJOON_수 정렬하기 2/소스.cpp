//ī���� ����: ���� �ߺ����� �����Ƿ� ������ ���� üũ�Ͽ� ���
//cin.tie(NULL), cin.sync_with_stdio(false)�� �Է� �ӵ� ����
//std::endl ��� '\n'�� ��� �ӵ� ���� ����

#include <iostream>
using namespace std;

bool argi[2000001] = { false };
int len = 0;

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);

	cin >> len;
	for (int i = 0, temp = 0; i < len; i++) {
		cin >> temp;
		temp += 1000000;
		argi[temp] = true;
	}

	for (int i = 0; i < 2000001; i++) {
		if (argi[i]) { cout << i - 1000000 << '\n'; }
	}

	return 0;
}