#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

typedef pair<int, int> pint;

constexpr int HOUSE = 1;
constexpr int CHICKEN = 2;

int n, m;
vector<pint> chic, house, cand_chic;
vector<bool> permu;

int get_dist(const pint& a, const pint& b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    /*
    * ���� ġŲ���� �и��Ͽ� ��ǥ�� ����
    * ��ĭ�� �ʿ� �����Ƿ� ����
    */
    cin >> n >> m;
    for (int i = 0, board; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board;

            if (board == HOUSE) {
                house.push_back(pint(i, j));
            }
            else if (board == CHICKEN) {
                chic.push_back(pint(i, j));
            }
        }
    }
    permu.resize(chic.size(), false);
    fill(permu.begin(), permu.begin() + m, true);

    /*
    * ��ü ġŲ�� �� m���� ����.
    * �� m���� �ּ� �Ÿ��� ����Ͽ� �ּڰ��� ������Ʈ�Ѵ�.
    */
    int res = INT32_MAX;
    do {
        for (int i = 0; i < permu.size(); i++) {
            if (permu[i]) {
                cand_chic.push_back(chic[i]);
            }
        }

        int tmp_res = 0;
        for (const pint& h : house) {
            int min_dist = INT32_MAX;

            for (const pint& c : cand_chic) {
                min_dist = min(min_dist, get_dist(h, c));
            }

            tmp_res += min_dist;
        }

        res = min(res, tmp_res);
        cand_chic.clear();
    } while (prev_permutation(permu.begin(), permu.end()));
    
    cout << res;
    
    return 0;
}