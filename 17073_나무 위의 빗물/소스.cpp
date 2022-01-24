#include <iostream>
#include <vector>

using namespace std;

int n, leaf_cnt = 0;
double water;
vector<int> graph[500001];
bool visit[500001];

void dfs(const int cur) {
    int child_cnt = 0;
    visit[cur] = true;
    
    for (const int adj : graph[cur]) {
        if (!visit[adj]) {
            child_cnt++;
        }
    }

    if (child_cnt == 0) {
        leaf_cnt++;
    }
    else {
        for (const int adj : graph[cur]) {
            if (!visit[adj]) {
                dfs(adj);
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * ���� �������� ���� ���� ��� ���� leaf ��忡 ���� ���̴�.
    * ����, ��ü ���� ���� leaf ����� ���� �����ָ�
    * ����� ���� �� �ִ�.
    */
    cin >> n >> water;
    for (int i = 0, n1, n2; i < n - 1; i++) {
        cin >> n1 >> n2;
        graph[n1].push_back(n2);
        graph[n2].push_back(n1);
    }

    dfs(1);

    cout.precision(10);
    cout << water / leaf_cnt;

    return 0;
}