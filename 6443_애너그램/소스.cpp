#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int testcase;
string str;

/*
* Ư�� ���ڿ��� ��� �ֳʱ׷��� ����ϸ� �ǹǷ�,
* algorithm ����� permutation�� �̿��ϸ� �ȴ�.
* ���ڿ��� ���ĺ� ������ ������ �Ŀ�,
* ������ ������ ������ָ� �ȴ�.
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