/*
	각 행에서 꺼진 갯수를 먼저 셈.
	만약 스위치 조작 회수가 홀수라면 꺼진 갯수가 홀수인 행을 찾고, 반대도 마찬가지.
	찾은 행들 중 꺼진 갯수가 최대인 것을 찾음.
*/

#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main() {
	int height, width;
	int ans = -1;
	string arr[50];

	cin >> height >> width;

	for (int y = 0; y < height; y++) {
		cin >> arr[y];
	}

	int k;
	cin >> k;

	for (int i = 0; i < height; i++) {
		int zeroCount = 0;
		for (int h = 0; h < width; h++) {
			if (arr[i][h] == '0') {
				zeroCount++;
			}
		}
		int sum = 0;
		if (zeroCount <= k && zeroCount % 2 == k % 2) {
			for (int y = 0; y < height; y++) {
				if (arr[i] == arr[y]) {
					sum++;
				}
			}
		}

		ans = max(sum, ans);
	}
	cout << ans;

	return 0;
}