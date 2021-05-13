#include <iostream>
#include <string>

using namespace std;

int main(){
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	
	int n = 0;
	cin >> n;

	long long s = 1, t = 10000000;
	for (long long i = 1, j = 1; i <= n; i++) {
		for (j = 1; (j <= s * i) && (s * i / j % 10 == 0); j *= 10);
		s = s * i / j % t;
	}
	
	s %= 100000;
	string out = "00000";
	for (int i = 4; i >= 0; i--) {
		out[i] += s % 10;
		s /= 10;
	}

	cout << out;

	return 0;
}