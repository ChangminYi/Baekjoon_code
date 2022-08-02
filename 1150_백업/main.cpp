#include <iostream>
#include <queue>

using namespace std;

struct pqn {
    int node;
    long long dist;
    pqn(const int _n, const long long _d) {
        node = _n, dist = _d;
    }
    bool operator>(const pqn& other) const {
        return dist > other.dist;
    }
};

int n, k, bef;
int left_node[100003], right_node[100003];
long long dist[100003];
bool visit[100003];
priority_queue<pqn, vector<pqn>, greater<>> pq;

int main() {
    /**
     * 가장 짧은 거리를 가진 건물들을 이어 나가면 된다. 하지만, 한 번 연결된
     * 건물은 다시는 접근할 수 없고, 연결되어 있는 좌우의 건물도 연결된 건물과
     * 연결할 수 없다. 따라서 건물 쌍이 연결되면, 해당 쌍의 거리를
     * 연결된 쌍의 좌우측 건물 간 거리에서 빼 주고, 연결된 쌍의 좌우측 건물을
     * 새로운 한 쌍으로 다시 묶어 주어야 한다. 이 과정을 k번 반복하면 최단 길이를 구할 수 있다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k >> bef;
    dist[1] = INT32_MAX, right_node[1] = 2;
    for (int i = 2, tmp; i <= n; i++, bef = tmp) {
        cin >> tmp;
        dist[i] = tmp - bef;
        left_node[i] = i - 1, right_node[i] = i + 1;
        pq.push(pqn(i, dist[i]));
    }
    dist[n + 1] = INT32_MAX, left_node[n + 1] = n;
    pq.push(pqn(1, dist[1])), pq.push(pqn(n + 1, dist[n + 1]));
    
    long long ans = 0;
    do {
        while (visit[pq.top().node]) pq.pop();
        
        int cur = pq.top().node;
        int cur_left = left_node[cur], cur_right = right_node[cur];
        ans += pq.top().dist;
        pq.pop();

        dist[cur] = dist[cur_left] + dist[cur_right] - dist[cur];
        visit[cur_left] = true, visit[cur_right] = true;
        left_node[cur] = left_node[cur_left], right_node[cur] = right_node[cur_right];
        cur_left = left_node[cur], cur_right = right_node[cur];
        right_node[cur_left] = cur, left_node[cur_right] = cur;

        pq.push(pqn(cur, dist[cur]));
    } while(--k);

    cout << ans;
    
    return 0;
}