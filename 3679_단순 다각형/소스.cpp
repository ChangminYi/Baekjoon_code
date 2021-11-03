#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long lli;

struct node {
    int x = 0, y = 0, idx = 0;
    
    bool operator<(const node& other) const {
        return (this->x == other.x ? this->y < other.y : this->x < other.x);
    }
    bool operator==(const node& other) const {
        return this->x == other.x && this->y == other.y;
    }
};

int testcase, n;
vector<node> arg;

// ccw �˰���.
int ccw(const node& a, const node& b, const node& c) {
    lli ret = (lli)a.x * b.y + (lli)b.x * c.y + (lli)c.x * a.y;
    ret -= (lli)a.y * b.x + (lli)b.y * c.x + (lli)c.y * a.x;

    return (ret == 0 ? 0 : (ret > 0 ? 1 : -1));
}

// �� �� ���� �Ÿ� ���.
double get_dist(const node& a, const node& b) {
    double diff_x = (double)a.x - b.x;
    double diff_y = (double)a.y - b.y;
    return sqrt(diff_x * diff_x + diff_y * diff_y);
}

// ���� �� ����ϴ� ���Լ�
bool cmp(const node& lhs, const node& rhs) {
    int ccw_res = ccw(arg[0], lhs, rhs);

    if (ccw_res == 0) {
        return get_dist(arg[0], lhs) < get_dist(arg[0], rhs);
    }
    else {
        return ccw_res > 0;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> testcase;
    do {
        cin >> n;
        arg.resize(n);

        for (int i = 0; i < n; i++) {
            cin >> arg[i].x >> arg[i].y;
            arg[i].idx = i;
        }

        // ���� ���� �Ʒ� ������ ù��° ���� ����.
        swap(arg[0], *min_element(arg.begin(), arg.end()));
        sort(arg.begin() + 1, arg.end(), cmp);

        /*
        * ������ �� �˰��� ���.
        * �ٸ�, ù��° ���� ������ ���� �մ� ���� ���� �ִ� ������
        * �Ÿ��� �� ������ �����ؾ� �ϱ� ������, �� ���� ���
        * reverse�� ���ش�.
        */
        int hi = n - 1;
        for (int i = n - 1; i >= 1; i--) {
            if (ccw(arg[0], arg[hi], arg[hi - 1]) == 0) {
                hi--;
            }
            else {
                break;
            }
        }
        reverse(arg.begin() + hi, arg.end());
        
        for (const node& n : arg) {
            cout << n.idx << ' ';
        }
        cout << '\n';
    } while (--testcase > 0);

    return 0;
}