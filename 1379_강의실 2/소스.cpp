#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>

using namespace std;

struct dat {
    int s_time = 0, e_time = 0, num = 0;
    dat() {}
    const bool operator<(const dat& other) const {
        return (this->s_time == other.s_time ? this->e_time < other.e_time : this->s_time < other.s_time);
    }
};
struct pqn {
    int time = 0, alloc_num = 0;
    pqn(int _t, int _an) : time(_t), alloc_num(_an) {}
    const bool operator>(const pqn& other) const {
        return this->time > other.time;
    }
};

int n;
dat arg[100000];
int alc[100001], tmp_alc[100001];

bool do_allocate(const int size) {
    priority_queue<pqn, vector<pqn>, greater<pqn>> pq;
    for (int i = 1; i <= size; i++) {
        pq.push(pqn(0, i));
    }

    for (int i = 0; i < n; i++) {
        if (arg[i].s_time >= pq.top().time) {
            tmp_alc[arg[i].num] = pq.top().alloc_num;
            pq.pop();
            pq.push(pqn(arg[i].e_time, tmp_alc[arg[i].num]));
        }
        else {
            return false;
        }
    }

    for (int i = 1; i <= n; i++) {
        alc[i] = tmp_alc[i];
    }
    return true;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arg[i].num >> arg[i].s_time >> arg[i].e_time;
    }

    sort(arg, arg + n);

    /*
    * ���Ǹ� ���� �ð� �������� ����. �� ��, �̺�Ž���� ���� ���ǽ� �� Ȯ��.
    * �̺�Ž���� �����ϸ鼭, ���ǽ� ������ ���� �Ѵ�. ���ǰ� ���������� ��
    * �����Ǿ��� ���� ���ǽ� ������ �����Ѵ�.
    */
    int k = 0;
    int lo = 1, hi = n;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;

        if (do_allocate(mid)) {
            k = mid;
            hi = mid - 1;
        }
        else {
            lo = mid + 1;
        }
    }

    cout << k << '\n';
    for (int i = 1; i <= n; i++) {
        cout << alc[i] << '\n';
    }

    return 0;
}