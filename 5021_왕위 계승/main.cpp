#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;

int n, m, p_cnt = 0;
int in_degree[151];
long double priority[151];
string sp, tmp[3], name_by_idx[151];
unordered_map<string, int> name_to_idx;
vector<int> graph[151];
queue<int> que;

int main() {
    /**
     * 위상 정렬을 통해 각 사람마다의 혈통의 값을 구할 수 있다.
     * 왕위 요구자 중 가족 정보에 이름이 없다면 넘어가도 무방하다.
     * 이름이 있는 경우에만 혈통 값을 비교하여 최대인 사람을 출력한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    cin >> sp;
    name_by_idx[p_cnt] = sp;
    priority[p_cnt] = (1LL << 61);
    name_to_idx.insert(make_pair(sp, p_cnt++));
    for(int i = 0; i < n; i++) {
        cin >> tmp[0] >> tmp[1] >> tmp[2];
        for(int j = 0; j < 3; j++) {
            if(name_to_idx.find(tmp[j]) == name_to_idx.end()) {
                name_by_idx[p_cnt] = tmp[j];
                name_to_idx.insert(make_pair(tmp[j], p_cnt++));
            }
        }

        in_degree[name_to_idx[tmp[0]]] += 2;
        graph[name_to_idx[tmp[1]]].push_back(name_to_idx[tmp[0]]);
        graph[name_to_idx[tmp[2]]].push_back(name_to_idx[tmp[0]]);
    }

    for(int i = 0; i < p_cnt; i++) {
        if(in_degree[i] == 0) que.push(i);
    }
    while(!que.empty()) {
        int cur = que.front();
        que.pop();

        for(const int& nxt: graph[cur]) {
            priority[nxt] += priority[cur];
            if(--in_degree[nxt] == 0) {
                priority[nxt] /= 2;
                que.push(nxt);
            }
        }
    }

    int max_idx = 0;
    long double max_p = -1;
    for(int i = 0, tmp_idx; i < m; i++) {
        cin >> tmp[0];
        if(name_to_idx.find(tmp[0]) == name_to_idx.end()) continue;

        tmp_idx = name_to_idx[tmp[0]];
        if(priority[tmp_idx] > max_p) {
            max_p = priority[tmp_idx];
            max_idx = tmp_idx;
        }
    }

    cout << name_by_idx[max_idx];

    return 0;
}