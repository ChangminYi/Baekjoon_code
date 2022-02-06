#include <iostream>
#include <numeric>

using namespace std;

int n, m, x, y;
int parent[1'000'001];

int do_find(const int x) {
    return parent[x] == x ? x : parent[x] = do_find(parent[x]);
}

void do_union(const int x, const int y) {
    int f_x = do_find(x), f_y = do_find(y);
    if (f_x < f_y) parent[f_x] = f_y;
    else parent[f_y] = f_x;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 분리집합으로 벽이 허물어진 상태를 표현할 수 있다.
    * 집합의 대푯값은 집합 중 가장 큰 값으로 설정한다.
    * x와 y의 집합이 같아질 때까지 union한다. union할 때 방의 크기를 하나 줄인다.
    * 모든 연산이 끝났을 때 n값이 남아있는 방의 수이다.
    */
    cin >> n >> m;
    iota(parent + 1, parent + n + 1, 1);

    while (m--) {
        cin >> x >> y;
        int fx, fy = do_find(y);
        while ((fx = do_find(x)) != fy) {
            do_union(do_find(x), do_find(x) + 1);
            n--;
        }
    }

    cout << n;

    return 0;
}