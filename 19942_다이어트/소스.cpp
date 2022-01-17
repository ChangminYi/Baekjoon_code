#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

struct dat {
    int prot, fat, carb, vit, cost;
};

dat arg[16];
int n, mp, mf, ms, mv;
int min_cost = INT32_MAX;
vector<vector<int>> ans_set;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> mp >> mf >> ms >> mv;
    for (int i = 0; i < n; i++) {
        cin >> arg[i].prot >> arg[i].fat >> arg[i].carb >> arg[i].vit >> arg[i].cost;
    }

    /*
    * n�� �ִ� 15�̹Ƿ�, ��� ����� ���� ��� �ð��ʰ��� ���� �ʴ´�.
    * ��� ����� ������ �� ������� ���� ���ϰ�, ���ǿ� ������ �ּҺ���
    * �׶� ����� �ε����� �ֽ�ȭ�Ѵ�. ���������� ���� ���� ���� ����ؾ� �ϹǷ�,
    * �ĺ� ������ �� �� �����ϰ� ���� ���� ���Ҹ� ����ϸ� �ȴ�.
    */
    for (int i = 1, sum_prot, sum_fat, sum_carb, sum_vit, sum_cost; i < (1 << n); i++) {
        sum_prot = 0;
        sum_fat = 0;
        sum_carb = 0;
        sum_vit = 0;
        sum_cost = 0;
        vector<int> tmp_set;

        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                tmp_set.push_back(j + 1);
                sum_prot += arg[j].prot;
                sum_fat += arg[j].fat;
                sum_carb += arg[j].carb;
                sum_vit += arg[j].vit;
                sum_cost += arg[j].cost;
            }
        }

        if (sum_prot >= mp && sum_fat >= mf && sum_carb >= ms && sum_vit >= mv) {
            if (min_cost > sum_cost) {
                min_cost = sum_cost;
                ans_set = vector<vector<int>>(1, tmp_set);
            }
            else if (min_cost == sum_cost) {
                ans_set.push_back(tmp_set);
            }
        }
    }

    if (min_cost == INT32_MAX) {
        cout << -1;
    }
    else {
        sort(ans_set.begin(), ans_set.end());
        cout << min_cost << '\n';
        for (const int i : ans_set.front()) {
            cout << i << ' ';
        }
    }

    return 0;
}