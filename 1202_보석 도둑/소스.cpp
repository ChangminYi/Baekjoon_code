#include <iostream>
#include <deque>
#include <queue>
#include <algorithm>

using namespace std;
typedef pair<int, int> pint;

int main() {
    cin.tie(nullptr);
    cin.sync_with_stdio(false);
    cout.tie(nullptr);
    cout.sync_with_stdio(false);

    int n_jew, n_bag;
    cin >> n_jew >> n_bag;

    deque<pint> jew(n_jew);
    for (pint &p: jew) {
        cin >> p.first >> p.second;
    }
    deque<int> bag(n_bag);
    for (int &i : bag) {
        cin >> i;
    }

    sort(jew.begin(), jew.end());
    sort(bag.begin(), bag.end());

    priority_queue<int> pq;
    long long sum_val = 0;
    while(!bag.empty()) {
        //���� �� �ִ� ������ ������ ��� pq�� ����
        while(!jew.empty() && jew.front().first <= bag.front()) {
            //pq���� ���� ���� ������ �ȴ�
            pq.push(jew.front().second);
            jew.pop_front();
        }

        if (!pq.empty()) {
            sum_val += pq.top();
            pq.pop();
        }
        bag.pop_front();
    }

    cout << sum_val;

    return 0;
}