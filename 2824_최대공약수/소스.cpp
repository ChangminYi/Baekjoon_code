#include <iostream>
#include <vector>
#include <unordered_map>
#include <iomanip>
#include <cmath>

using namespace std;

#define MAX 1000000000

typedef long long lli;
typedef unordered_map<int, int> umap;

vector<int> prime = { 2, 3 };

void init_prime() {
	for (int i = prime.back() + 2; i <= (int)sqrt(MAX); i += 2) {
		bool divisible = false;

		for (int j = 0; prime[j] <= (int)sqrt(i); j++) {
			if (i % prime[j] == 0) {
				divisible = true;
				break;
			}
		}

		if (!divisible) {
			prime.push_back(i);
		}
	}
}

void prime_fact(int to_fact, umap& cont) {
	for (size_t i = 0; i < prime.size() && to_fact > 1; i++) {
		if (to_fact % prime[i] == 0) {
			cont.insert(make_pair(prime[i], 0));
			while (to_fact % prime[i] == 0) {
				cont[prime[i]]++;
				to_fact /= prime[i];
			}
		}
	}

	if (to_fact > 1) {
		cont.insert(make_pair(to_fact, 1));
	}
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	init_prime();

	umap count_a, count_b;
	bool divided = false;
	lli res = 1;
	int n_a = 0, n_b = 0;

	cin >> n_a;
	for (int i = 0, temp; i < n_a; i++) {
		cin >> temp;
		prime_fact(temp, count_a);
	}
	cin >> n_b;
	for (int i = 0, temp; i < n_b; i++) {
		cin >> temp;
		prime_fact(temp, count_b);
	}

	for (umap::iterator i = count_a.begin(); i != count_a.end(); i++) {
		int prm = (*i).first;
		umap::iterator j = count_b.find(prm);

		if (j != count_b.end()) {
			int exp = min((*i).second, (*j).second);

			while (exp > 0) {
				res *= prm;
				exp--;

				if (res > MAX) {
					divided = true;
					res %= MAX;
				}
			}
		}
	}

	if (divided) {
		cout.width(9);
		cout.fill('0');
	}
	cout << res;

	return 0;
}