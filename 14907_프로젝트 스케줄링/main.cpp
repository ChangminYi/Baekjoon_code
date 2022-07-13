#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cmath>

using namespace std;

string input;
int in_degree[26], cost[26], dp[26];
vector<int> graph[26];
queue<int> que;

int main() {
    /**
     * 입력의 수가 미정이므로, getline으로 더 이상 입력이 없을 때까지 입력을 받는다.
     * 각 노드와 선행조건들을 이용하여 그래프를 구축하고, 위상 정렬을 통해 노드를 탐색한다.
     * 이 과정에서 해당 노드에 도착할 때까지 소요되는 최대 시간을 저장한다.
     * 더 이상 진행할 수 없는 끝점들에서 비용의 최댓값을 구하면 그 값이 시간의 최솟값.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);
    
    while(getline(cin, input)) {
        int idx1 = -1, idx2 = -1;
        for(int i = 0; i < input.length(); i++) {
            if(input[i] == ' ')
                (idx1 == -1 ? idx1 = i : idx2 = i);
        }

        cost[input[0] - 'A'] = (idx2 == -1 ? stoi(input.substr(2)) : stoi(input.substr(2, idx2 - idx1 - 1)));
        if(idx2 != -1) {
            for(int i = idx2 + 1; i < input.length(); i++) {
                graph[input[i] - 'A'].push_back(input[0] - 'A');
                in_degree[input[0] - 'A']++;
            }
        }
    }

    int ans = 0;
    for(int i = 0; i < 26; i++) {
        if(in_degree[i] == 0) {
            dp[i] = cost[i];
            que.push(i);
        }
    }
    while(!que.empty()) {
        int cur = que.front();
        que.pop();

        if(graph[cur].empty())
            ans = max(ans, dp[cur]);
        else {
            for(const int& nxt: graph[cur]) {
                dp[nxt] = max(dp[nxt], dp[cur] + cost[nxt]);
                if(--in_degree[nxt] == 0)
                    que.push(nxt);
            }
        }
    }

    cout << ans;

    return 0;
}