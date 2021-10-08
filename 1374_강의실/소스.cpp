#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

int n, tmp;
size_t max_size = 0;
vector<pint> argi;
priority_queue<int, vector<int>, greater<int>> pq;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    
    argi.resize(n);
    for (pint& p : argi) {
        cin >> tmp >> p.first >> p.second;
    }

    /*
    * ��� ���Ǹ� ���� �ð������� �����ϰ�, �������� �Ѵ�. 
    * ���� ������ ���� �ð����� �۰ų� ���� ��� ���Ǹ� ���ְ�,
    * ���� ������ ������ �ð��� pq�� �ִ´�.
    * �ִ� �ʿ��� ���ǽ� ���� pq�� �ִ� ũ��� ����.
    */
    sort(argi.begin(), argi.end());
    for (const pint& p : argi) {
        while (!pq.empty() && pq.top() <= p.first) {
            pq.pop();
        }
        pq.push(p.second);

        max_size = max(max_size, pq.size());
    }

    cout << max_size;

    return 0;
}