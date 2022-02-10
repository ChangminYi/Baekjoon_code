#include <iostream>
#include <string>
#include <set>

using namespace std;

int n, m, arg1, arg2;
string inst;
set<int> lev_set, prob_set[101];
int prov_lev[100'001];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * 문제의 번호-레벨 관계 테이블, 레벨-번호 집합을 동시에 유지하여
    * recommend 명령어가 입력되면 레벨-번호 집합을 사용하여 최대/최소를 빠르게 찾는다.
    * add, solved 명령어가 입력되면 번호-레벨 테이블을 통해 해당 레벨
    * 집합에서 문제를 제거하고, 레벨의 최대/최소까지 최신화한다.
    */

    cin >> n;
    for (int i = 0, p, l; i < n; i++) {
        cin >> p >> l;
        prov_lev[p] = l;
        lev_set.insert(l);
        prob_set[l].insert(p);
    }
    cin >> m;

    do {
        cin >> inst;
        if (inst == "recommend") {
            cin >> arg1;
            if (arg1 == 1) {
                cout << *(--prob_set[*(--lev_set.end())].end()) << '\n';
            }
            else {
                cout << *(prob_set[*lev_set.begin()].begin()) << '\n';
            }
        }
        else if (inst == "add") {
            cin >> arg1 >> arg2;
            prov_lev[arg1] = arg2;
            lev_set.insert(arg2);
            prob_set[arg2].insert(arg1);
        }
        else {
            cin >> arg1;
            prob_set[prov_lev[arg1]].erase(arg1);
            if (prob_set[prov_lev[arg1]].empty()) {
                lev_set.erase(prov_lev[arg1]);
            }
        }
    } while (--m);

    return 0;
}