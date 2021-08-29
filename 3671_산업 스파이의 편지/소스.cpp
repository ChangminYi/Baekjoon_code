#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

vector<int> prime = { 2, 3 };
vector<bool> visit;
string nums;
unordered_set<int> poss_set;

void init_prime() {
	for (int i = 5; i * i <= 10000000; i += 2) {
		bool is_prime = true;
		for (int j = 0; prime[j] * prime[j] <= i; j++) {
			if (i % prime[j] == 0) {
				is_prime = false;
				break;
			}
		}

		if (is_prime) {
			prime.push_back(i);
		}
	}
}

bool is_prime(int n) {
	if (n <= 1) {
		return false;
	}
	else {
		for (int& p : prime) {
			if (p * p > n) {
				break;
			}
			else {
				if (n % p == 0) {
					return false;
				}
			}
		}
		return true;
	}
}

void find_prime(int cur, int val) {
	if (is_prime(val) && poss_set.find(val) == poss_set.end()) {
		poss_set.insert(val);
	}

	for (size_t i = 0; i < nums.length(); i++) {
		if (!visit[i]) {
			visit[i] = true;
			find_prime(i, 10 * val + (nums[i] - '0'));
			visit[i] = false;
		}
	}
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	init_prime();
	int testcase;
	cin >> testcase;

	do {
		nums.clear();
		poss_set.clear();
		cin >> nums;
		visit = vector<bool>(nums.length(), false);

		for (size_t i = 0; i < nums.length(); i++) {
			visit[i] = true;
			find_prime(i, nums[i] - '0');
			visit[i] = false;
		}

		cout << poss_set.size() << '\n';
	} while (--testcase > 0);

	return 0;
}