#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef pair<int, int> pint;

int n;
vector<pint> arg;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    arg.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> arg[i].first;
        arg[i].second = i;
    }

    sort(arg.begin(), arg.end());

    /*
    * 버블 소트는 한 번 루프를 돌면 최대 한 칸 좌측으로 가므로,
    * 정렬하기 전과 정렬한 후의 인덱스 차이를 보면 된다.
    */
    int max_dist = 0;
    for (int i = 0; i < n; i++) {
        max_dist = max(max_dist, arg[i].second - i);
    }

    cout << max_dist + 1;

    return 0;
}