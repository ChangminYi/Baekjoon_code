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
	* ��� ���� n���� ��带 ���� Ʈ���� �𵨸� �� �� �ִ�. ��Ʈ�� ���Ƿ� 0���� ����.
	* 0���� ������ ��ü ����� �ּҰ������ ������ ����. dfs�� �����ϸ鼭 ������ ����� ���� ����.
	* �׸��� ��� �� ��ü�� �ִ������� ������ ������ �����־� ����ϸ� �ȴ�.
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

