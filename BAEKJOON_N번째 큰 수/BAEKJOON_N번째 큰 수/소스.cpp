#include <iostream>
#include <deque>
#include <algorithm>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	int N = 0;
	cin >> N;
	deque<int> argi(N*N);
	for (int &i : argi) {
		cin >> i;
	}
	sort(argi.begin(), argi.end());
	cout << argi[N * N - N];

	return 0;
}