#include <iostream>
#include <queue>

using namespace std;

typedef class STATUS {
public:
	int cur_num;
	int clipboard;
	int time;
	STATUS() {};
	STATUS(int _num, int _clip, int _time) : cur_num(_num), clipboard(_clip), time(_time) {};
} status;

bool isInRange(int i) {
	if (0 <= i && i <= 1000) {
		return true;
	}
	return false;
}

int main() {
	int ans = 0;
	cin >> ans;

	vector<bool> check(1001, false);
	queue<status> togo;
	togo.push(status(1, 0, 0));
	while (true) {
		status now = togo.front();
		check[now.cur_num] = true;
		togo.pop();

		if (now.cur_num == ans) {
			cout << now.time;
			break;
		}
		else {
			if (now.cur_num - 1 >= 0 && !check[now.cur_num-1]) {
				togo.push(status(now.cur_num - 1, now.clipboard, now.time + 1));
			}
			if (now.clipboard != 0 && !check[now.cur_num+now.clipboard]) {
				togo.push(status(now.cur_num + now.clipboard, now.clipboard, now.time + 1));
			}
			togo.push(status(now.cur_num, now.cur_num, now.time + 1));
		}
	}

	return 0;
}