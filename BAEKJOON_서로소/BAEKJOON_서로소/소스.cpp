#include <iostream>
#include <deque>
#include <cmath>
#include <algorithm>

#define MAX 1000000000
using namespace std;

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	deque<int> prime = { 2, 3 };
	bool isDivisible = false;
	for (int i = 5; i <= sqrt(MAX); i += 2) {
		for (size_t j = 0; prime[j] <= sqrt(i); j++) {
			if (i % prime[j] == 0) {
				isDivisible = true;
				break;
			}
		}

		if (!isDivisible) {
			prime.push_back(i);
		}
		isDivisible = false;
	}

	while (true) {
		int n = 0;
		cin >> n;

		if (n == 0) {
			break;
		}
		else {
			int res = 1;
			pair<int, int> temp = make_pair(0, 0);
			int to_comp = n;
			for (size_t i = 0; to_comp > 1 && i < prime.size(); i++) {
				if (to_comp % prime[i] == 0) {
					temp = make_pair(prime[i], 0);
					
					while (to_comp % prime[i] == 0) {
						to_comp /= prime[i];
						temp.second++;
					}
					res *= (int)pow(temp.first, temp.second - 1) * (temp.first - 1);
				}
			}

			if (to_comp != 1) {
				res *= to_comp - 1;
			}

			cout << res << '\n';
		}
	}


	return 0;
}