#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

typedef pair<int, int> pint;

int n, min_class = 0;
vector<pint> time_set;
priority_queue<int, vector<int>, greater<int>> pq;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    time_set.resize(n);
    for (pint& p : time_set) {
        cin >> p.first >> p.second;
    }
    sort(time_set.begin(), time_set.end());

    /*
    * ���� �ð� ������ �ð��� ������ ��, ������ �ð��� Ȯ��.
    * �켱���� ť���� ������ ������ �ð��� ������������ ����.
    * �켱���� ť�� ũ�Ⱑ ����� ���� �����̴�.
    * ���� �켱���� ť�� ����ִٸ�, �ٷ� ���� �����ִ� ������ ������ �ð� ����.
    * ���� ť�� �������� ���� ������ ���� �ð����� �۴ٸ�, ���� �濡�� �� �� ����.
    * �׷��Ƿ� ť���� pop�ϰ�, ���� ������ ������ �ð� ����.
    * �ƴ϶��, ���� �濡�� ������ �� ����. �׷��Ƿ� �ٷ� ������ �ð� ����.
    */
    for (int i = 0; i < n; i++) {
        if (pq.empty()) {
            pq.push(time_set[i].second);
        }
        else {
            if (time_set[i].first >= pq.top()) {
                pq.pop();
            }

            pq.push(time_set[i].second);
        }

        min_class = max<int>(min_class, pq.size());
    }

    cout << min_class;

    return 0;
}