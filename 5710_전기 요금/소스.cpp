#include <iostream>

using namespace std;

long long get_cost(long long usage) {
	long long ret = 0;

	if (usage > 100) {
		ret += 200;
		usage -= 100;

		if (usage > 9900) {
			ret += 29700;
			usage -= 9900;

			if (usage > 990000) {
				ret += 4950000;
				usage -= 990000;

				if (usage > 0) {
					ret += usage * 7;
				}
			}
			else {
				ret += usage * 5;
			}
		}
		else {
			ret += usage * 3;
		}
	}
	else {
		ret += usage * 2;
	}

	return ret;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	while (true) {
		long long A, B;
		cin >> A >> B;

		if (A == 0 && B == 0) {
			break;
		}
		else {
			long long total_cost = A;
			long long total_use = 0;

			if (A > 200) {
				total_use += 100;
				A -= 200;

				if (A > 29700) {
					total_use += 9900;
					A -= 29700;

					if (A > 4950000) {
						total_use += 990000;
						A -= 4950000;

						if (A > 0) {
							total_use += A / 7;
							A = 0;
						}
					}
					else {
						total_use += A / 5;
					}
				}
				else {
					total_use += A / 3;
				}
			}
			else {
				total_use += A / 2;
			}

			long long lft = 0, rgt = total_use;
			while (lft <= rgt) {
				long long mid = (lft + rgt) / 2;
				long long val_mid = get_cost(mid), val_counter = get_cost(total_use - mid);
				if (val_counter - val_mid == B) {
					cout << val_mid << '\n';
					break;
				}
				else {
					if (val_counter - val_mid > B) {
						lft = mid + 1;
					}
					else {
						rgt = mid - 1;
					}
				}
			}
		}
	}

	return 0;
}