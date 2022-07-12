#include <iostream>
#include <vector>

using namespace std;

int n, m, k;
vector<int> graph[100001];
int in_degree[100001], cnt[100001];

int main() {
    /**
     * 위상 정렬을 응용하여 해결할 수 있다.
     * 건물이 지어졌다면, 해당 건물이 지어질 수 있는지 in_degree가 0인지로 판단할 수 있다.
     * 가능하다면, 해당 건물의 수를 올리고 만약 처음 지어졌다면 다음 노드들의 in_degree를 줄인다.
     * 건물이 무너졌다면, 해당 건물이 존재하는지 cnt가 0이 아닌지를 확인한다.
     * 가능하다면, 해당 건물의 수를 내리고 더 이상 건물이 없다면 다음 노드들의 in_degree를 올린다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);
    
    cin >> n >> m >> k;
    for(int from, to; m; m--) {
        cin >> from >> to;
        graph[from].push_back(to);
        in_degree[to]++;
    }

    bool flag = true;
    for(int inst, cur; k && flag; k--) {
        cin >> inst >> cur;
        if(inst == 1) {
            if(in_degree[cur] != 0)
                flag = false;
            else {
                if(cnt[cur]++ == 0) {
                    for(const int& nxt: graph[cur])
                        in_degree[nxt]--;
                }
            }
        }
        else {
            if(cnt[cur] == 0)
                flag = false;
            else {
                if(--cnt[cur] == 0) {
                    for(const int& nxt: graph[cur])
                        in_degree[nxt]++;
                }
            }
        }
    }

    cout << (flag ? "King-God-Emperor" : "Lier!");

    return 0;
}