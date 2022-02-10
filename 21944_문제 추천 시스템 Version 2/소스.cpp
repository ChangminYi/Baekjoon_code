#include <iostream>
#include <set>
#include <string>

using namespace std;

int n, m, p, l, g, x;
string inst;
set<int>::iterator iter;
set<int> exist_lev, lev_set[101];
set<int> exist_alg_lev[101], alg_lev_set[101][101];
int problem_lev[100'001], problem_alg[100'001];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    /*
    * ��ü ���̵��� �˰��� ���̵� ���̺��� ���� ����.
    * ���� �� ���� �˻��� ���� ����-����, ����-�˰��� ���̺� ����.
    * ���� �� ����ִ� set�� �ٷ� exist ��Ͽ��� ������ ������ ����.
    */

    cin >> n;
    do {
        cin >> p >> l >> g;
        problem_lev[p] = l, problem_alg[p] = g;
        exist_lev.insert(l), lev_set[l].insert(p);
        exist_alg_lev[g].insert(l), alg_lev_set[g][l].insert(p);
    } while (--n);
    cin >> m;
    do {
        cin >> inst;

        if (inst == "recommend") {
            cin >> g >> x;
            if (x == 1) cout << *(--alg_lev_set[g][*(--exist_alg_lev[g].end())].end()) << '\n';
            else cout << *alg_lev_set[g][*exist_alg_lev[g].begin()].begin() << '\n';
        }
        else if (inst == "recommend2") {
            cin >> x;
            if (x == 1) cout << *(--lev_set[*(--exist_lev.end())].end()) << '\n';
            else cout << *lev_set[*exist_lev.begin()].begin() << '\n';
        }
        else if (inst == "recommend3") {
            cin >> x >> l;
            iter = exist_lev.lower_bound(l);
            if (x == 1) {
                if (iter == exist_lev.end()) cout << "-1\n";
                else cout << *lev_set[*iter].begin() << '\n';
            }
            else {
                if (iter == exist_lev.begin()) cout << "-1\n";
                else cout << *(--lev_set[*(--iter)].end()) << '\n';
            }
        }
        else if (inst == "add") {
            cin >> p >> l >> g;
            problem_lev[p] = l, problem_alg[p] = g;
            exist_lev.insert(l), lev_set[l].insert(p);
            exist_alg_lev[g].insert(l), alg_lev_set[g][l].insert(p);
        }
        else {
            cin >> p;
            l = problem_lev[p], g = problem_alg[p];
            lev_set[l].erase(p);
            alg_lev_set[g][l].erase(p);
            if (lev_set[l].empty()) exist_lev.erase(l);
            if (alg_lev_set[g][l].empty()) exist_alg_lev[g].erase(l);
        }
    } while (--m);

    return 0;
}