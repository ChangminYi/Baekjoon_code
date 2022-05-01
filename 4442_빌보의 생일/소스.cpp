#include <iostream>
#include <unordered_map>

using namespace std;

const int MAX_SIZE = 400'005;

int n;
string tmp;
long long ans;
long long segtree[MAX_SIZE];
unordered_map<string, int> order;

void update_segtree(int idx, int lo, int hi, int offset) {
    if (lo == hi) segtree[idx]++;
    else {
        int mid = (lo + hi) / 2;
        if (offset <= mid) update_segtree(2 * idx, lo, mid, offset);
        else update_segtree(2 * idx + 1, mid + 1, hi, offset);
        segtree[idx] = segtree[2 * idx] + segtree[2 * idx + 1];
    }
}

long long get_query(int idx, int lo, int hi, int left, int right) {
    if (lo == left && hi == right) return segtree[idx];
    else {
        int mid = (lo + hi) / 2;
        if (right <= mid) return get_query(2 * idx, lo, mid, left, right);
        else if (mid < left) return get_query(2 * idx + 1, mid + 1, hi, left, right);
        else return get_query(2 * idx, lo, mid, left, mid) + get_query(2 * idx + 1, mid + 1, hi, mid + 1, right);
    }
}

int main() {
    /*
    * inversion counting 문제. 한 노드에 간선이 단 1개 연결되므로,
    * 중복을 처리하지 않아도 된다. 들어오는 문자열을 순서대로 번호를 매겨
    * 반대편 노드의 번호로 사용하면 간선을 정렬하지 않아도 된다.
    */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    while (true) {
        cin >> n;
        if (n == 0) break;

        order.clear();
        fill(segtree, segtree + MAX_SIZE, 0);
        ans = 0;

        for (int i = 0; i < n; i++) {
            cin >> tmp;
            order.insert(make_pair(tmp, i));
        }

        for (int i = 0, offset; i < n; i++) {
            cin >> tmp;
            offset = order[tmp];
            ans += get_query(1, 0, n - 1, offset, n - 1);
            update_segtree(1, 0, n - 1, offset);
        }

        cout << ans << '\n';
    }

    return 0;
}