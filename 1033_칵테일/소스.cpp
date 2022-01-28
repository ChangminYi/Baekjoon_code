#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int n;
long long mass[10];
int ratio[10][10];
vector<int> graph[10];
bool visit[10];

void dfs(const int cur) {
	visit[cur] = true;
	for (const int& nxt : graph[cur]) {
		if (!visit[nxt]) {
			mass[nxt] = (mass[cur] * ratio[cur][nxt]) / ratio[nxt][cur];
			dfs(nxt);
		}
	}
}

int main(void) {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	/*
	* 재료 쌍을 n개의 노드를 가진 트리로 모델링 할 수 있다. 루트는 임의로 0으로 설정.
	* 0번의 질량을 전체 재료의 최소공배수의 곱으로 설정. dfs를 실행하면서 나머지 재료의 질량 구함.
	* 그리고 출력 시 전체의 최대공약수로 각각의 질량을 나눠주어 출력하면 된다.
	*/
	cin >> n;
	mass[0] = 1;
	for (int i = 0, a, b, p, q; i < n - 1; i++) {
		cin >> a >> b >> p >> q;
		graph[a].push_back(b), graph[b].push_back(a);
		ratio[a][b] = q, ratio[b][a] = p;
		mass[0] *= lcm(p, q);
	}

	dfs(0);

	long long total_gcd = mass[0];
	for (int i = 1; i < n; i++) {
		if (mass[i]) {
			total_gcd = gcd(total_gcd, mass[i]);
		}
	}

	for (int i = 0; i < n; i++) {
		cout << mass[i] / total_gcd << ' ';
	}

	return 0;
}

