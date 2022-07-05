#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

typedef long long lli;

int q;
lli arg[200000][3], search_val[200000], seg[800100];
vector<lli> dir;
set<lli> zero_point;

void update_seg(int idx, int lo, int hi, int dest) {
    if(dest < lo || dest > hi) return;
    else if (lo == hi) seg[idx]++;
    else {
        int mid = (lo + hi) / 2;
        if(dest <= mid) update_seg(2 * idx, lo, mid, dest);
        else update_seg(2 * idx + 1, mid + 1, hi, dest);
        seg[idx] = seg[2 * idx] + seg[2 * idx + 1];
    }
}

lli get_query(int idx, int lo, int hi, int left, int right) {
    if(lo > right || hi < left) return 0;
    else if(left <= lo && hi <= right) return seg[idx];
    else {
        int mid = (lo + hi) / 2;
        lli res1 = get_query(2 * idx, lo, mid, left, right);
        lli res2 = get_query(2 * idx + 1, mid + 1, hi, left, right);
        return res1 + res2;
    }
}

int main() {
    /**
     * 전체 함수의 최고차항의 부호를 관리하고, 세그먼트 트리를 사용하여
     * 1번 쿼리에 대한 함수 추가를 관리한다. 좌표는 모두 정수로 관리하여도 무방하다.
     * 2번 쿼리에서, c값에 대해서 자신보다 큰 좌표의 수가 홀수이면 음수, 아니면 짝수이고
     * 이를 최고차항 부호와 곱하여 부호의 값을 얻는다. 좌표의 범위가 매우 넓으므로
     * 미리 1번 쿼리에 대해서 좌표 압축을 실행한 후에 쿼리를 처리해야 한다.
     * 0으로 나눠 떨어지는 좌표는 따로 관리하여 2번 쿼리에서 확인하여 0을 출력할지 결정.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> q;
    lli tmp_val;
    for (int i = 0; i < q; i++) {
        cin >> arg[i][0] >> arg[i][1];
        if (arg[i][0] == 1) {
            cin >> arg[i][2];

            if (arg[i][1] != 0) {
                lli tmp_b = arg[i][1], tmp_c = -arg[i][2];
                if((tmp_b > 0 && tmp_c < 0) || (tmp_b < 0 && tmp_c > 0)) tmp_val = (tmp_c / tmp_b) - (tmp_c % tmp_b != 0);
                else tmp_val = tmp_c / tmp_b;
                dir.push_back(tmp_val);
            }
        }
        else {
            tmp_val = arg[i][1];
            dir.push_back(tmp_val);
        }
        search_val[i] = tmp_val;
    }

    sort(dir.begin(), dir.end());
    dir.erase(unique(dir.begin(), dir.end()), dir.end());

    int k = 1;
    for(int i = 0; i < q; i++) {
        if(arg[i][0] == 1) {
            if(arg[i][1] == 0) {
                if(arg[i][2] == 0) k = 0;
                else k = arg[i][2] > 0 ? k : -k;
            }
            else {
                int idx = lower_bound(dir.begin(), dir.end(), search_val[i]) - dir.begin() + 1;
                update_seg(1, 1, dir.size(), idx);
                if(arg[i][2] % arg[i][1] == 0) 
                    zero_point.insert(-arg[i][2] / arg[i][1]);
                k = arg[i][1] > 0 ? k : -k;
            }
        }
        else {
            int idx = lower_bound(dir.begin(), dir.end(), search_val[i]) - dir.begin() + 1;
            int status = k * (get_query(1, 1, dir.size(), idx, dir.size()) % 2 == 0 ? 1 : -1);

            if(status == 0 || zero_point.find(search_val[i]) != zero_point.end()) cout << "0\n";
            else cout << (status > 0 ? "+\n" : "-\n");
        }
    }

    return 0;
}