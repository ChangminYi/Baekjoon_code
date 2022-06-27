#include <iostream>
#include <set>
#include <queue>

using namespace std;

int n, k, str_len, iter;
queue<int> que;
set<int> visit;

int main() {
    /**
     * bfs를 사용하여 가능한 수를 탐색한다. 구현의 편의성을 위해
     * int를 string으로 변환하여 탐색하였다. k번 숫자를 바꾼 뒤에
     * 가장 큰 값을 출력하는 것이기 때문에, 각 bfs의 레벨마다
     * visit이 초기화되어야 한다. 이전의 탐색은 현재의 탐색에 영향을 주면 안된다.
     * k번째 레벨까지 탐색하고, visit에 값이 있다면 가장 큰 값을 출력한다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k;
    str_len = to_string(n).length();
    que.push(n);
    for(iter = 0; iter < k && !que.empty(); iter++) {
        int qs = que.size();
        do {
            int cur = que.front();
            string cur_str = to_string(cur);
            que.pop();

            for(int i = 0; i < str_len - 1; i++) {
                for(int j = i + 1; j < str_len; j++) {
                    if(i == 0 && cur_str[j] == '0') 
                        continue;
                    else {
                        swap(cur_str[i], cur_str[j]);
                        int nxt = stoi(cur_str);
                        swap(cur_str[i], cur_str[j]);

                        if(visit.find(nxt) == visit.end()) {
                            visit.insert(nxt);
                            que.push(nxt);
                        }
                    }
                }
            }
        } while(--qs);

        if(iter != k - 1) visit.clear();
    }

    cout << (iter == k && !visit.empty() ? *--visit.end() : -1);

    return 0;
}