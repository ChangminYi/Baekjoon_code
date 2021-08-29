#include <iostream>
#include <vector>
#include <map>
#include <cmath>

using namespace std;
typedef unsigned long long lli;

const lli MAX = 1000000000L;
vector<lli> prime = {2, 3};

void init_prime() {
	for (lli i = 5; i <= sqrt(MAX); i += 2) {
		bool divided = false;
		for (lli& p : prime) {
			if (i % p == 0) {
				divided = true;
				break;
			}
		}
		if (!divided) {
			prime.push_back(i);
		}
	}
}

map<lli, lli> factorization(lli n) {
	map<lli, lli> facts;

	if (n > 0) {
		for (uint32_t i = 0; i < prime.size(); i++) {
			while (n % prime[i] == 0) {
				if (facts.find(prime[i]) == facts.end()) {
					facts.insert(make_pair(prime[i], 1L));
				}
				else {
					facts[prime[i]]++;
				}
				n /= prime[i];
			}
		}
		if (n > 1) {
			facts.insert(make_pair(n, 1L));
		}
	}

	return facts;
}

lli get_GCD(lli a, lli b) {
	if (b == 0) {
		return a;
	}
	else {
		return get_GCD(b, a % b);
	}
}

lli get_LCM(lli a, lli b) {
	lli gcd = get_GCD(a, b);
	return (gcd * (a / gcd) * (b / gcd));
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	init_prime();
	uint32_t size_d, size_m;
	cin >> size_d >> size_m;
	vector<lli> D = vector<lli>(size_d);	//LCM
	vector<lli> M = vector<lli>(size_m);	//GCD
	for (lli& i : D) {
		cin >> i;
	}
	for (lli& i : M) {
		cin >> i;
	}

	lli D_LCM = D[0], M_GCD = M[0];
	for (uint32_t i = 1; i < D.size(); i++) {
		D_LCM = get_LCM(D_LCM, D[i]);
	}
	for (uint32_t i = 1; i < M.size(); i++) {
		M_GCD = get_GCD(M_GCD, M[i]);
	}

	lli res = 1;
	if (M_GCD % D_LCM == 0) {
		map<lli, lli> dist = factorization(M_GCD / D_LCM);
		for (map<lli, lli>::iterator i = dist.begin(); i != dist.end(); i++) {
			res *= i->second + 1;
		}
	}
	else {
		res = 0;
	}
	cout << res;

	return 0;
}