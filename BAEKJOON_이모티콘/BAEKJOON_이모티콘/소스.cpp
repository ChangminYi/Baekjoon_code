#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef struct STATUS {
	int screen;
	int clipboard;
	int time;
}status;

#define MAX 10001

vector<vector<bool>> visit(MAX, vector<bool>(MAX, false));

int main() {
	cin.tie(nullptr);
	cin.sync_with_stdio(false);
	cout.tie(nullptr);
	cout.sync_with_stdio(false);

	int n = 0;
	cin >> n;

	queue<status> to_go;
	to_go.push({1, 0, 0});
	visit[1][0] = true;
	while (!to_go.empty()) {
		status cur = to_go.front();
		to_go.pop();

		if (cur.screen == n) {
			cout << cur.time;
			break;
		}
		else {
			if (cur.clipboard != 0) {
				if (!visit[cur.screen + cur.clipboard][cur.clipboard]) {
					visit[cur.screen + cur.clipboard][cur.clipboard] = true;
					to_go.push({ cur.screen + cur.clipboard, cur.clipboard, cur.time + 1 });
				}
			}
			if (cur.screen > 0) {
				if (!visit[cur.screen][cur.screen]) {
					visit[cur.screen][cur.screen] = true;
					to_go.push({ cur.screen, cur.screen, cur.time + 1 });
				}
				if (!visit[cur.screen - 1][cur.clipboard]) {
					visit[cur.screen - 1][cur.clipboard] = true;
					to_go.push({ cur.screen - 1, cur.clipboard, cur.time + 1 });
				}
			}
		}
	}

	return 0;
}