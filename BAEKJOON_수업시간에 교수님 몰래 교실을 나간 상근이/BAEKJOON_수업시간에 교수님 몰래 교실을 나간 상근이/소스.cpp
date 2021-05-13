/*
	시간초과
	문자열끼리 비교는 O(n)인데 이중for문 해결해야될듯
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool hasSameNumber(const string &a, const string &b) {
	vector<bool> table = vector<bool>(10, false);
	for (uint32_t i = 0; i < a.size(); i++) {
		table[a[i] - '0'] = true;
	}
	for (uint32_t i = 0; i < b.size(); i++) {
		if (table[b[i] - '0']) { return true; }
	}
	return false;
}

int main() {
	cin.tie(NULL); cin.sync_with_stdio(false);

	int N = 0;
	cin >> N;

	vector<string> args = vector<string>(N);
	for (int i = 0, temp = 0; i < N; i++) {
		cin >> temp;
		args[i] = to_string(temp);
	}

	int count = 0;
	for (int i = 0; i < N - 1; i++) {
		for (int j = i+1; j < N; j++) {
			if (hasSameNumber(args[i], args[j])) { count++; }
		}
	}

	cout << count;

	return 0;
}