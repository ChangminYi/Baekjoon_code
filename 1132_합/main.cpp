#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct dat {
    int idx;
    bool is_first;
    long long val;
    dat() {
        idx = 0, is_first = false, val = 0;
    }
};

int n, latest_idx;
dat cnt[10];
string tmp;

int get_idx(char c) {
    return c - 'A';
}

int main() {
    /**
     * 알파벳이 등장하는 자릿수를 모두 더하여, 가장 큰 값부터 9부터 할당.
     * 단, 가장 앞에 나오는 값이 0이 되면 안되므로, 만약 첫 글자가 마지막 순서라면
     * 첫 글자가 아닌 것 중 가장 자릿수 합이 작은 것을 골라 그 값을 마지막으로 할당.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    for(int i = 0; i < 10; i++) {
        cnt[i].idx = i;
    }

    (cin >> n).ignore();
    for(int i = 0; i < n; i++) {
        cin >> tmp;
        long long deci = 1;
        cnt[get_idx(tmp[0])].is_first = true;
        for(int i = tmp.length() - 1, idx; i >= 0; i--, deci *= 10) {
            idx = get_idx(tmp[i]);
            cnt[idx].val += deci;
            latest_idx = max(latest_idx, idx);
        }
    }

    sort(cnt, cnt + 10, [](dat lhs, dat rhs) {
        return lhs.val > rhs.val;
    });

    if(cnt[latest_idx].is_first) {
        int base = INT32_MIN;
        for(int i = latest_idx - 1; i >= 0; i--) {
            if(!cnt[i].is_first) {
                base = i;
                break;
            }
        }

        if(base != INT32_MIN) {
            dat tmp = cnt[base];
            for(int i = base + 1; i <= latest_idx; i++) {
                cnt[i - 1] = cnt[i];
            }
            cnt[latest_idx] = tmp;
        }
    }

    long long ans = 0;
    for(int i = 0; i <= latest_idx; i++) {
        ans += (9 - i) * cnt[i].val;
    }

    cout << ans;

    return 0;
}
