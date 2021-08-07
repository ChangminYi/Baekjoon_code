#include <iostream>
#include <cmath>

using namespace std;

int n;
int low_base, high_base;

bool is_prime(const int test) {
	if (test == 2) {
		return true;
	}
	if (test % 2 == 0) {
		return false;
	}
	else {
		for (int i = 3; i * i <= test; i += 2) {
			if (test % i == 0) {
				return false;
			}
		}

		return true;
	}
}

void search_prime(int now) {
	if (low_base <= now && now < high_base) {
		cout << now << '\n';
	}
	else{
		for (int i = 1, tmp; i <= 9; i += 2) {
			tmp = 10 * now + i;
			if (is_prime(tmp)) {
				search_prime(tmp);
			}
		}
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	low_base = (int)pow(10, n - 1);
	high_base = (int)pow(10, n);

	search_prime(2);
	search_prime(3);
	search_prime(5);
	search_prime(7);

	return 0;
}