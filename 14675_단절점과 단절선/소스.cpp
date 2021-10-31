#include <iostream>
#include <vector>

using namespace std;

int n, t;
vector<int> degree;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    degree.resize(n + 1);
    for (int i = 1, a, b; i < n; i++) {
        cin >> a >> b;
        degree[a]++, degree[b]++;
    }

    cin >> t;
    for (int i = 0, inst, arg; i < t; i++) {
        cin >> inst >> arg;

        if (inst == 1) {
            /*
            * 트리에서는, 연결된 노드가 2개 이상이면 반드시 단절점.
            * 사이클이 존재하지 않기 때문.
            */
            cout << (degree[arg] <= 1 ? "no\n" : "yes\n");
        }
        else {
            /*
            * 사이클이 없기 때문에, 트리의 모든 간선은 단절선.
            */
            cout << "yes\n";
        }
    }

    return 0;
}