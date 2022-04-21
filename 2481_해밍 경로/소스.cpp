#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <numeric>

using namespace std;

const int NO_PARENT = -1;
const int START = 1;

int n, k, m;
string tmp;
int value[100'000];
map<int, int> index_map;
vector<int> graph[100'001];
bool visit[100'001];
int parent[100'001];
stack<int> trace;
queue<int> que;

void bfs() {
    visit[START] = true;
    que.push(START);
    while (!que.empty()) {
        int cur = que.front();
        que.pop();

        for (const int nxt : graph[cur]) {
            if (!visit[nxt]) {
                visit[nxt] = true;
                parent[nxt] = cur;
                que.push(nxt);
            }
        }
    }
}

int get_hamming_dist(const int lhs, const int rhs) {
    int ret = 0;
    for (int diff = lhs ^ rhs; diff != 0; diff >>= 1) {
        if (diff & 1) {
            ret++;
        }
    }
    return ret;
}

int main() {
    /*
    * ���ڿ� ���� �񱳴� ������尡 ũ�� ������, ���ڷ� ��ȯ�Ͽ� ���.
    * map�� ����Ͽ� ���ڿ��� ���ڰ��� Ű, ���� ������ ������ �Ͽ� ����.
    * XOR ��Ʈ ������ ���� �� �� ���� �ع� �Ÿ��� ���Ѵ�.
    * �̸� ���� �׷����� ������ ����, �ڽ��� ���� ��带 ����ϸ鼭 bfs ����.
    * �׸��� bfs ���߿� �湮�� ����� ��θ� �������Ͽ� ����ϰ�, �ƴ϶�� -1 ���.
    */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        for (int j = 0; j < k; j++) {
            if (tmp[k - 1 - j] == '1') {
                value[i] |= (1 << j);
            }
        }
        index_map.insert(make_pair(value[i], i + 1));
    }

    sort(value, value + n);
    for (int i = 0, cur, nxt; i < n; i++) {
        cur = value[i];
        for (int j = 0; j < k; j++) {
            if ((cur & (1 << j)) == 0) {
                nxt = cur | (1 << j);
                if (binary_search(value, value + n, nxt) && get_hamming_dist(cur, nxt) == 1) {
                    graph[index_map[cur]].push_back(index_map[nxt]);
                    graph[index_map[nxt]].push_back(index_map[cur]);
                }
            }
        }
    }

    fill(parent + 1, parent + n + 1, NO_PARENT);
    bfs();

    cin >> m;
    for (int dest; m > 0; m--) {
        cin >> dest;
        if (visit[dest]) {
            for (int cur = dest; cur != NO_PARENT; cur = parent[cur]) {
                trace.push(cur);
            }

            for (; !trace.empty(); trace.pop()) {
                cout << trace.top() << ' ';
            }
            cout << '\n';
        }
        else {
            cout << "-1\n";
        }
    }

    return 0;
}
