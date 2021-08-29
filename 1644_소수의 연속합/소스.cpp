//using deque rather than list is much efficient in terms of memory

#include <iostream>
#include <list>
#include <cmath>

using namespace std;

list<int> prime = { 2, 3 };

void add_prime() {
	for (int i = prime.back() + 2; ; i += 2) {
		bool divisible = false;


		for (list<int>::iterator j = prime.begin()++; *j <= sqrt(i); j++) {
			if (i % *j == 0) {
				divisible = true;
				break;
			}
		}

		if (!divisible) {
			prime.push_back(i);
			break;
		}
	}

	return;
}

bool is_prime(int to_test) {
	for (list<int>::iterator i = prime.begin(); *i <= sqrt(to_test); i++) {
		if (to_test % *i == 0) {
			return false;
		}
	}
	return true;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	list<int>::iterator frt = prime.begin(), bck = --prime.end();
	int N = 0, sum = 5, cnt = 0;
	cin >> N;

	if (N > 1) {
		while (*frt < *bck) {
			if (sum < N) {
				add_prime();
				sum += *(++bck);
			}
			else {
				if (sum == N) {
					cnt++;
				}
				sum -= *(frt++);
			}
		}

		if (is_prime(N)) {
			cnt++;
		}

	}

	cout << cnt;

	return 0;
}