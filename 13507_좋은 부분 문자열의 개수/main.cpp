#include <iostream>
#include <string>
#include <bitset>
#include <unordered_set>

using namespace std;

int k;
string str, tmp;
bitset<26> is_bad;
unordered_set<string> visit;
int presum[1501];

int main() {
    /**
     * 부분 문자열의 길이를 기준으로 반복문을 돌린다. 서로 다른 부분 문자열만을
     * 세야 하므로, 이미 카운트한 부분 문자열은 set에 따로 저장한다. 이 때,
     * 하나의 길이에 대하여 반복이 끝나면 메모리 절약을 위해 visit을 초기화한다.
     * 나쁜 알파벳의 수를 세는 법은 슬라이딩 윈도우와 같이 이동하면서 바로바로 업데이트.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> str >> tmp >> k;

    for(int i = 0; i < 26; i++) {
        is_bad[i] = (tmp[i] == '0');
    }

    for(int i = 0; i < str.length(); i++) {
        presum[i + 1] = presum[i];
        if(is_bad[str[i] - 'a']) presum[i + 1]++;
    }

    int ans = 0;
    for(int len = 1; len <= str.length(); len++) {
        int lo = 0, hi = len - 1, cnt = presum[len];
        while(true) {
            if(cnt <= k && visit.find(str.substr(lo, len)) == visit.end()) {
                visit.insert(str.substr(lo, len));
                ans++;
            }

            if(++hi == str.length()) break;
            if(is_bad[str[hi] - 'a']) cnt++;
            if(is_bad[str[lo++] - 'a']) cnt--;
        }

        visit.clear();
    }

    cout << ans;

    return 0;
}