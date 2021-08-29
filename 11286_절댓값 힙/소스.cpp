#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

typedef struct INTEGER {
public:
	int val;
	INTEGER() : val(0) {};
	INTEGER(int _i) : val(_i) {};
}INT;

bool operator< (INT a, INT b) {
	if (abs(a.val) == abs(b.val)) { return a.val > b.val; }
	return abs(a.val) > abs(b.val);
}

int main() {
	cin.tie(nullptr); cin.sync_with_stdio(false);

	priority_queue<INT, vector<INT>> pq;
	int N = 0;
	cin >> N;
	for (int i = 0; i < N; i++) {
		int temp = 0;
		cin >> temp;

		if (temp == 0) {
			if (pq.empty()) { cout << 0 << '\n'; }
			else { cout << pq.top().val << '\n'; pq.pop(); }
		}
		else {
			pq.push(INT(temp));
		}
	}

	return 0;
}