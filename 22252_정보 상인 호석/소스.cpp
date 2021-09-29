#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

typedef long long lli;

int n;
lli total_cost;
unordered_map<string, priority_queue<int>> seller;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    /*
    * 상인 이름과 우선순위 큐를 짝으로 묶어서 저장
    * 나머지는 쿼리에 맞게 구현
    */
    do {
        int inst, inf_size;
        string s_name;
        cin >> inst >> s_name >> inf_size;

        if (inst == 1) {
            if (seller.find(s_name) == seller.end()) {
                seller.insert(make_pair(s_name, priority_queue<int>()));
            }
            for (int i = 0, tmp; i < inf_size; i++) {
                cin >> tmp;
                seller[s_name].push(tmp);
            }
        }
        else {
            if (seller.find(s_name) != seller.end()) {
                for (int i = 0; i < inf_size && !seller[s_name].empty(); i++) {
                    total_cost += seller[s_name].top();
                    seller[s_name].pop();
                }
            }
        }
    } while (--n > 0);

    cout << total_cost;

    return 0;
}