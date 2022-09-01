#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct edge {
    int node, max_w;
    edge(const int _n, const int _mw) {
        node = _n, max_w = _mw;
    }
};

struct qn {
    int node, visit_bit;
    qn(const int _n, const int _vb) {
        node = _n, visit_bit = _vb;
    }
};

const int NOT_VISIT = -1;

int n, m, k;
int tr_num[101];
bool visit[1 << 14][101];
vector<edge> graph[101];
queue<qn> q;

int get_tr_cnt(int _vb) {
    int ret = 0;
    for(; _vb; _vb >>= 1)
        if(_vb & 1) ret++;
    return ret;
}

int main() {
    /**
     * 어떤 보석을 주웠는지를 비트마스킹을 통해 관리할 수 있다.
     * 가능한 모든 경우에 대해서 bfs를 진행한다. 진행 과정에서
     * 1번 노드에 도착할 때마다 가장 많이 주울 수 있는 보석의 수를
     * 갱신한다. bfs가 끝난 후 최댓값을 출력하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> k;
    fill(tr_num + 1, tr_num + n + 1, NOT_VISIT);
    for(int i = 0, tmp; i < k; i++) {
        cin >> tmp;
        tr_num[tmp] = i;
    }
    for(int a, b, c; m--; ) {
        cin >> a >> b >> c;
        graph[a].push_back(edge(b, c));
        graph[b].push_back(edge(a, c));
    }

    int ans = 0;
    visit[0][1] = true;
    q.push(qn(1, 0));
    while(!q.empty()) {
        int cur = q.front().node;
        int cur_vb = q.front().visit_bit;
        q.pop();

        int cur_cnt = get_tr_cnt(cur_vb);
        if(cur == 1) ans = max(ans, cur_cnt);
        for(const edge& e: graph[cur]) {
            if(cur_cnt > e.max_w) continue;

            int nxt = e.node;
            if(!visit[cur_vb][nxt]) {
                visit[cur_vb][nxt] = true;
                q.push(qn(nxt, cur_vb));
            }
            if(tr_num[nxt] != NOT_VISIT && !(cur_vb & (1 << tr_num[nxt]))) {
                visit[cur_vb | (1 << tr_num[nxt])][nxt] = true;
                q.push(qn(nxt, cur_vb | (1 << tr_num[nxt])));
            }
        }
    }

    cout << ans;

    return 0;
}