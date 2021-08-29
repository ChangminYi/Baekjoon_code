#include <iostream>
#include <string>
#include <deque>

using namespace std;

int main(void) {
	cin.sync_with_stdio(false);
	cin.tie(nullptr);

	int N = 0, K = 0;
	cin >> N >> K;

	string s;
	cin >> s;

	deque<char> deq;

	for (int i = 0; i < N; i++) {
		while (K > 0 && !deq.empty() && deq.back() < s[i]) {
			deq.pop_back();
			K--;
		}

		deq.push_back(s[i]);
	}

	for (uint32_t i = 0; i < deq.size() - K; i++) {
		cout << deq[i];
	}

	return 0;
}