#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int n, m, k;
vector<int> card, parent;

int find_parent(int x) {
    return (parent[x] == x ? x : parent[x] = find_parent(parent[x]));
}

void union_elem(int x, int y) {
    int f_x = find_parent(x), f_y = find_parent(y);
    if (f_x >= f_y) {
        swap(f_x, f_y);
    }
    parent[f_x] = f_y;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> k;
    card.resize(m);
    parent.resize(m + 1);
    for (int& i : card) {
        cin >> i;
    }
    iota(parent.begin(), parent.end(), 0);
    sort(card.begin(), card.end());

    /*
    * 한번 사용한 카드는 다시는 사용할 수 없음.
    * 따라서, 사용한 카드의 다음 카드와 같은 집합으로 묶어준다.
    * 집합의 대표값을 가장 큰 값으로 설정하면, find_parent를 실행할 때
    * 가장 큰 인덱스 값이 반환된다. 따라서, 같은 수가 입력으로 들어와도
    * 조건에 맞는 출력을 할 수 있게 된다.
    */
    do {
        int low_bnd;
        cin >> low_bnd;

        auto ub = upper_bound(card.begin(), card.end(), low_bnd);
        int idx = find_parent(distance(card.begin(), ub));
        cout << card[idx] << '\n';

        union_elem(idx, idx + 1);
    } while (--k > 0);

    return 0;
}