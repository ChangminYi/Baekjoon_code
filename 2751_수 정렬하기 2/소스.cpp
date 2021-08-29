//카운팅 정렬: 수가 중복되지 않으므로 등장한 수만 체크하여 출력
//cin.tie(NULL), cin.sync_with_stdio(false)로 입력 속도 증가
//std::endl 대신 '\n'이 출력 속도 많이 빠름

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