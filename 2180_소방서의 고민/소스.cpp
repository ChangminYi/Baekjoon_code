#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

const long long MOD = 40'000;

int n;
long long sum = 0;
pint arg[200'000];

bool cmp(const pint& lhs, const pint& rhs) {
	if (lhs.first == 0) return false;
	else if (rhs.first == 0) return true;
	else if (lhs.second == 0 && rhs.second == 0) return lhs.first < rhs.first;
	else return  lhs.second * rhs.first < rhs.second * lhs.first;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	/*
	* �ð��� �������� ���� ���� �ð��� �� ���� �ɸ��� ȭ�縦 ���� �����ؾ� �Ѵ�.
	* 0���� ������ ��쿡 ���ؼ� ����ó���� ���ָ� �ȴ�.
	* ������ �� ��, ���� ȭ�縦 ������ ������ �ɸ� �ð��� �������� ������ ���
	* �� �ɸ� �ð��� ����ϸ� �ȴ�.
	*/

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arg[i].first >> arg[i].second;
	}

	sort(arg, arg + n, cmp);
	
	for (int i = 0; i < n; i++) {
		sum += ((sum * arg[i].first) % MOD) + arg[i].second;
		sum %= MOD;
	}
	
	cout << sum;

	return 0;
}