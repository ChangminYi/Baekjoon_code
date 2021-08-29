#include <iostream>
#include <deque>
#include <vector>

using namespace std;

typedef struct NODE {
	int position;
	int time;
}node;

bool isInRange(int pos) {
	if (0 <= pos && pos <= 100000) {
		return true;
	}
	return false;
}

int main() {
	int N = 0, K = 0;
	cin >> N >> K;

	vector<bool> visit(100001, false);
	deque<node> q;
	q.push_back({ N, 0 });
	while (!q.empty()) {
		node cur = q.front();
		visit[cur.position] = true;
		q.pop_front();

		if (cur.position == K) {
			cout << cur.time;
			break;
		}
		else {
			if (isInRange(cur.position + 1) && !visit[cur.position + 1]) {
				q.push_back({ cur.position + 1, cur.time + 1 });
			}
			if (isInRange(cur.position - 1) && !visit[cur.position - 1]) {
				q.push_back({ cur.position - 1, cur.time + 1 });
			}
			if (isInRange(cur.position * 2) && !visit[cur.position * 2]) {
				q.push_front({ cur.position * 2, cur.time });
			}
		}
	}


	return 0;
}