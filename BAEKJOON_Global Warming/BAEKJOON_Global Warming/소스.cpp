#include <iostream>
#include <vector>

using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);

	while (true) {
		int N = 0;
		cin >> N;
		
		if (N == 0) {
			break;
		}
		else {
			vector<int> patt(N - 1);
			int last = 0, now = 0;
			cin >> last;
			for (int i = 0; i < N - 1; i++) {
				cin >> now;
				patt[i] = now - last;
				last = now;
			}

			bool breakFlag = false;
			for (int i = 1; i < N / 2; i++) {
				vector<int> smallpatt = vector<int>(patt.begin(), patt.begin() + i);
				for (int j = i; j < N; j += i) {
					if (j + i >= N) {
						for (int k = 0; k < N - j; k++) {
							if (smallpatt[k] != patt[k + j]) {
								cout << patt.size();
							}
							else if (k + j == N - 1) {
								cout << smallpatt.size();
							}
						}
						breakFlag = true;
						break;
					}
					else if (smallpatt != vector<int>(patt.begin() + j, patt.begin() + j + i)) {
						break;
					}
					else {
						continue;
					}
				}
				if (breakFlag) {
					break;
				}
			}
		}
	}

	return 0;
}