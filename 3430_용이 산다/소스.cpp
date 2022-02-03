#include <iostream>
#include <queue>
#include <functional>

using namespace std;

int z, n, m, ans_cnt;
bool flag;
int arg[1'000'001], rain_day_back[1000'001], nxt_rain[1'000'001], ans[1'000'001];
bool water_empty[1'000'001];
priority_queue<int, vector<int>, greater<>> pq;

void init() {
	flag = true;
	ans_cnt = 0;
	fill(rain_day_back, rain_day_back + n + 1, 0);
	fill(nxt_rain, nxt_rain + m + 1, 0);
	fill(water_empty, water_empty + n + 1, false);
	pq = priority_queue<int, vector<int>, greater<>>();
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);
	
	/*
	* 비어있는 호수에 비가 오는 가장 빠른 날을 우선순위 큐에 저장한다.
	* logn 시간에 호수 상태를 업데이트할 수 있다.
	* 호수에 비가 오는 날을 호수 번호마다 연결하여 빠르게 다음 날을 얻는다.
	* 물이 차 있는데 비가 오게 되면 실패한 것이고, 물이 비어 있다면 계속 이어간다.
	*/
	cin >> z;
	do  {
		cin >> n >> m;
		init();

		for (int i = 1; i <= m; i++) {
			cin >> arg[i];
			if (arg[i] != 0) {
				if (rain_day_back[arg[i]]) {
					nxt_rain[rain_day_back[arg[i]]] = i;
				}
				else {
					pq.push(i);
				}
				rain_day_back[arg[i]] = i;
			}
		}

		for (int i = 1; i <= m; i++) {
			if (arg[i] != 0) {
				if (water_empty[arg[i]]) {
					water_empty[arg[i]] = false;
					if (nxt_rain[i]) {
						pq.push(nxt_rain[i]);
					}
				}
				else {
					flag = false;
					break;
				}
			}
			else {
				if (!pq.empty()) {
					int cur = arg[pq.top()];
					pq.pop();
					water_empty[cur] = true;
					ans[ans_cnt++] = cur;
				}
				else {
					ans[ans_cnt++] = 0;
				}
			}
		}

		if (flag) {
			cout << "YES\n";
			for (int i = 0; i < ans_cnt; i++) {
				cout << ans[i] << (i + 1 == ans_cnt ? '\n' : ' ');
			}
		}
		else {
			cout << "NO\n";
		}
	} while (--z);

	return 0;
}