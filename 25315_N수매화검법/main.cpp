#include <iostream>
#include <algorithm>

using namespace std;

typedef long long lli;
typedef pair<lli, lli> plli;
struct node {
    plli p1, p2;
    lli weight;
    bool operator<(const node& other) const {
        return weight < other.weight;
    }
};

int n, cross_cnt[2500];
node arg[2500];

int ccw(const plli& a, const plli& b, const plli& c) {
    lli tmp = a.first * b.second + b.first * c.second + c.first * a.second;
    tmp -= a.second * b.first + b.second * c.first + c.second * a.first;
    
    if(tmp == 0) return 0;
    else return (tmp < 0 ? -1 : 1);
}

bool is_cross(const plli& x1, const plli& x2, const plli& y1, const plli &y2) {
    return ccw(x1, x2, y1) * ccw(x1, x2, y2) < 0 && ccw(y1, y2, x1) * ccw(y1, y2, x2) < 0;
}

int main() {
    /**
     * 두 선분이 교차한다면, 가중치가 더 낮은 것을 먼저 행하는 것이
     * 이득이다. 따라서, 가중치 오름차순으로 정렬한 후 ccw를 사용하여
     * 뒤의 경로들 중 겹치는 것의 수를 세고, 총 가중치 합을 계산하면 된다.
     */

    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> arg[i].p1.first >> arg[i].p1.second >> arg[i].p2.first >> arg[i].p2.second >> arg[i].weight;
    }

    sort(arg, arg + n);

    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(is_cross(arg[i].p1, arg[i].p2, arg[j].p1, arg[j].p2))
                cross_cnt[i]++;
        }
    }

    lli ans = 0;
    for(int i = 0; i < n; i++) {
        ans += (cross_cnt[i] + 1) * arg[i].weight;
    }

    cout << ans;

    return 0;
}
