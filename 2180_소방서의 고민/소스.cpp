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
	* 시간이 지날수록 불을 끄는 시간이 더 오래 걸리는 화재를 먼저 진압해야 한다.
	* 0으로 나누는 경우에 대해서 예외처리를 해주면 된다.
	* 정렬을 한 후, 직전 화재를 진압할 때까지 걸린 시간을 방정식의 변수로 삼아
	* 총 걸린 시간을 계산하면 된다.
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