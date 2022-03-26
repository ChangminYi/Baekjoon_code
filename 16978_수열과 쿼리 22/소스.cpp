#include <iostream>
#include <algorithm>

using namespace std;

struct query {
    int left, right, inst_1_idx, seq;
    bool operator<(const query& other) { return inst_1_idx < other.inst_1_idx; }
};

int n, m, cnt_inst_1 = 0, cnt_inst_2 = 0;
long long segtree[400'001], ans[100'000];
int inst_1[100'000][2];
query inst_2[100'000];

void update_seg(int idx, int lo, int hi, int new_idx, int new_val) {
    if (lo == hi) {
        segtree[idx] = new_val;
    }
    else {
        int mid = (lo + hi) / 2;
        if (new_idx <= mid) update_seg(2 * idx, lo, mid, new_idx, new_val);
        else update_seg(2 * idx + 1, mid + 1, hi, new_idx, new_val);
        segtree[idx] = segtree[2 * idx] + segtree[2 * idx + 1];
    }
}

long long get_query(int idx, int lo, int hi, int left, int right) {
    if (lo == left && hi == right) {
        return segtree[idx];
    }
    else {
        int mid = (lo + hi) / 2;
        if (right <= mid) {
            return get_query(2 * idx, lo, mid, left, right);
        }
        else if (mid < left) {
            return get_query(2 * idx + 1, mid + 1, hi, left, right);
        }
        else {
            long long ret_1 = get_query(2 * idx, lo, mid, left, mid);
            long long ret_2 = get_query(2 * idx + 1, mid + 1, hi, mid + 1, right);
            return ret_1 + ret_2;
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 오프라인 쿼리. 들어온 쿼리의 순서를 바꾸어서 처리한 후, 다시 원래 순서로
    * 돌려놓아 쿼리 처리를 최적화한다. 2번 명령의 순서를 기억하여, 1번 쿼리의
    * 진행 상황을 기준으로 오름차순 정렬한 뒤, 1번 쿼리를 실행하면서 답을 구하고
    * 원래 2번 쿼리의 순서에 맞게 저장하여 한꺼번에 출력하면 된다.
    */

    cin >> n;
    for (int i = 1, val; i <= n; i++) {
        cin >> val;
        update_seg(1, 1, n, i, val);
    }
    cin >> m;
    for (int i = 0, inst; i < m; i++) {
        cin >> inst;
        if (inst == 1) {
            cin >> inst_1[cnt_inst_1][0] >> inst_1[cnt_inst_1][1];
            cnt_inst_1++;
        }
        else {
            cin >> inst_2[cnt_inst_2].inst_1_idx >> inst_2[cnt_inst_2].left >> inst_2[cnt_inst_2].right;
            inst_2[cnt_inst_2].seq = cnt_inst_2;
            cnt_inst_2++;
        }
    }

    sort(inst_2, inst_2 + cnt_inst_2);
    for (int i = 0, update_cnt = 0; i < cnt_inst_2; i++) {
        while (update_cnt < inst_2[i].inst_1_idx) {
            update_seg(1, 1, n, inst_1[update_cnt][0], inst_1[update_cnt][1]);
            update_cnt++;
        }
        ans[inst_2[i].seq] = get_query(1, 1, n, inst_2[i].left, inst_2[i].right);
    }

    for (int i = 0; i < cnt_inst_2; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}