#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

#define LEN 100001

typedef struct NODE {
	int dir, time;
}node;

vector<bool> check = vector<bool>(LEN, false);
queue<node> togo;

bool isInRange(int i) {
	if (0 <= i && i < LEN) {
		return true;
	}
	return false;
}

int main() {
	int N = 0, K = 0;
	cin >> N >> K;

	int sameCount = 1;
	togo.push({ N, 0 });
	while (!togo.empty()) {
		int curDir = togo.front().dir;
		int curTime = togo.front().time;
		check[curDir] = true;
		togo.pop();

		if (curDir == K) {
			cout << curTime << '\n';
			while (!togo.empty()) {
				if (togo.front().dir == K && togo.front().time == curTime) {
					sameCount++;
				}
				togo.pop();
			}
			cout << sameCount;
		}
		else {
			if (isInRange(curDir + 1) && !check[curDir + 1]) {
				togo.push({ curDir + 1, curTime + 1 });
			}
			if (isInRange(curDir - 1) && !check[curDir - 1]) {
				togo.push({ curDir - 1, curTime + 1 });
			}
			if (isInRange(curDir * 2) && !check[curDir * 2]) {
				togo.push({ curDir * 2, curTime + 1 });
			}
		}
	}

	return 0;
}