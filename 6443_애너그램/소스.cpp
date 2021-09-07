#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int testcase;
string str;

/*
* 특정 문자열의 모든 애너그램을 출력하면 되므로,
* algorithm 헤더의 permutation을 이용하면 된다.
* 문자열을 알파벳 순으로 정렬한 후에,
* 각각의 조합을 출력해주면 된다.
*/
int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> testcase;
	do {
		cin >> str;

		sort(str.begin(), str.end());
		do {
			cout << str << '\n';
		} while (next_permutation(str.begin(), str.end()));
	} while (--testcase > 0);

	return 0;
}