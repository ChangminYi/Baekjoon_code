#include <iostream>
#include <vector>

using namespace std;

bool is_in_array(int _srch, vector<int>& argi) {
	if (!argi.empty()) {
		for (const int& i : argi) {
			if (_srch == i) {
				return true;
			}
		}
	}
	return false;
}

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int N, K;
	cin >> N >> K;
	vector<int> seque(K);
	vector<int> plugged;
	for (int &i : seque) {
		cin >> i;
	}

	int swap_cnt = 0;
	for (int i = 0; i < K; i++) {
		bool plugged_in = is_in_array(seque[i], plugged);

		if (!plugged_in) {
			if (plugged.size() < N) {
				plugged.push_back(seque[i]);
			}
			else {
				int max_val = 0, swap_idx = 0;
				for (int k = 0; k < N; k++) {
					bool break_flag = false;

					for (int j = i + 1; j < K; j++) {
						if (plugged[k] == seque[j]) {
							if (j > max_val) {
								max_val = j;
								swap_idx = k;
							}
							break;
						}
						else if (j == K - 1) {
							swap_idx = k;
							break_flag = true;
						}
					}
					if (break_flag) {
						break;
					}
				}

				plugged[swap_idx] = seque[i];
				swap_cnt++;
			}
		}
	}

	cout << swap_cnt;
	
	return 0;
}