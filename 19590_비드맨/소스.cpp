//???????
//출력에 규칙이 있다고 함
//(총합-최댓값)이 최댓값보다 클 경우와 아닌 경우

#include <iostream>
using namespace std;

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);

	int n = 0;
	cin >> n;

	long long total = 0;
	int max = 0;
	for (int i = 0, temp = 0; i < n; i++) {
		cin >> temp;
		total += temp;
		if (temp > max) { max = temp; }
	}
	
	if (max >= total - max) {
		cout << max - (total - max);
	}
	else {
		cout << total % 2;
	}
	return 0;
}