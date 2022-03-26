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
    * �������� ����. ���� ������ ������ �ٲپ ó���� ��, �ٽ� ���� ������
    * �������� ���� ó���� ����ȭ�Ѵ�. 2�� ����� ������ ����Ͽ�, 1�� ������
    * ���� ��Ȳ�� �������� �������� ������ ��, 1�� ������ �����ϸ鼭 ���� ���ϰ�
    * ���� 2�� ������ ������ �°� �����Ͽ� �Ѳ����� ����ϸ� �ȴ�.
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