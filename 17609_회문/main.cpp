#include <iostream>

using namespace std;

int t;
string str;

pair<bool, bool> is_palin(int lo, int hi, bool branched) {
    pair<bool, bool> ret = make_pair(false, false);
    
    while(true) {
        if(lo > hi) {
            ret.first = true, ret.second = true;
            break;
        }
        else if(str[lo] == str[hi]) {
            lo++, hi--;
        }
        else {
            if(!branched) {
                pair<bool, bool> res_1, res_2;
                res_1 = is_palin(lo + 1, hi, true), res_2 = is_palin(lo, hi - 1, true);
                if(res_1.first || res_2.first) {
                    ret.first = true;
                }
            }
            break;
        }
    }

    return ret;
}

int main() {
    /**
     * 문자열의 가장 끝부터 회문인지를 검사한다.
     * 만약 서로 다른 글자를 만나면, 왼쪽을 올리는 것과 오른쪽을 내리는 것으로
     * 한 번 분기하여 다시 회문인지를 검사한다. 이 결과에 따라서 정답을 출력하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> t;
    do {
        cin >> str;
        pair<bool, bool> res = is_palin(0, str.length() - 1, false);

        if(res.first) cout << (res.second ? "0\n" : "1\n");
        else cout << "2\n";
    } while(--t);

    return 0;
}