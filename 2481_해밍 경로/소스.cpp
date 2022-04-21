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
    * 문자열 간의 비교는 오버헤드가 크기 때문에, 숫자로 변환하여 계산.
    * map을 사용하여 문자열의 숫자값을 키, 들어온 순서를 값으로 하여 저장.
    * XOR 비트 연산을 통해 두 수 간의 해밍 거리를 구한다.
    * 이를 통해 그래프를 구축한 다음, 자신의 직전 노드를 기억하면서 bfs 실행.
    * 그리고 bfs 도중에 방문한 노드라면 경로를 역추적하여 출력하고, 아니라면 -1 출력.
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
