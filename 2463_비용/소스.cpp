#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;
typedef pair<int, pint> edge;
typedef long long lli;

const lli MOD = 1000000000;

int n, m;
lli sum = 0, res = 0;
vector<int> parent, set_size;
vector<edge> arg;

int find_parent(const int x) {
    return (parent[x] == x ? x : (parent[x] = find_parent(parent[x])));
}

void union_elem(const int x, const int y) {
    int f_x = find_parent(x), f_y = find_parent(y);
    if (f_x > f_y) {
        swap(f_x, f_y);
    }

    parent[f_y] = f_x;
    set_size[f_x] += set_size[f_y];
    set_size[f_y] = 0;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    parent.resize(n + 1);
    set_size.resize(n + 1, 1);
    arg.resize(m);

    iota(parent.begin(), parent.end(), 0);
    for (int i = 0; i < m; i++) {
        cin >> arg[i].second.first >> arg[i].second.second >> arg[i].first;
        
        // u < v를 만들어주기 (필수는 아님)
        if (arg[i].second.first > arg[i].second.second) {
            swap(arg[i].second.first, arg[i].second.second);
        }
        sum += arg[i].first;
    }

    /*
    * 간선의 가중치 기준으로 내림차순 정렬.
    * 간선을 계속 추가하다가, 특정 간선을 추가했을 때 정점들의 집합이
    * 합쳐지는 순간이 원래대로라면 Cost(u, v)를 구하는 순간.
    * 따라서, 합쳐지는 순간에 남아있는, 아직 추가되지 않은 간선(Cost를 구하기 위해 삭제되는 간선)과
    * 이들을 포함하는 집합의 수를 계산하여 총 합을 구할 수 있음.
    */
    sort(arg.rbegin(), arg.rend());

    for (int i = 0, p1, p2, weight; i < m; i++) {
        p1 = find_parent(arg[i].second.first);
        p2 = find_parent(arg[i].second.second);
        weight = arg[i].first;

        if (p1 != p2) {
            // 자료형 범위 조심.
            res += ((((lli)set_size[p1] * set_size[p2]) % MOD) * sum) % MOD;
            res %= MOD;

            union_elem(p1, p2);
        }

        sum -= weight;
    }

    cout << res;

    return 0;
}