#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>

using namespace std;

struct line {
    double min_tan = 0, max_tan = 0;

    line(double x1, double y1, double x2, double y2) {
        double line_tmp1 = y1 / x1;
        double line_tmp2 = y2 / x2;

        min_tan = min(line_tmp1, line_tmp2);
        max_tan = max(line_tmp1, line_tmp2);
    }
    bool operator<(const line& rhs) const {
        if (this->min_tan == rhs.min_tan) {
            return this->max_tan < rhs.max_tan;
        }
        else {
            return this->min_tan < rhs.min_tan;
        }
    }
};

int n;
vector<line> arg_line;
priority_queue<double, vector<double>, greater<double>> pq;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for (int i = 0, x1, x2, y1, y2; i < n; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        arg_line.push_back(line(x1, y1, x2, y2));
    }

    sort(arg_line.begin(), arg_line.end());
    
    /*
    * 선분의 기울기에 대한 스위핑
    * 최저 기울기와 최대 기울기를 구하여 기울기 순으로 정렬한 후,
    * 우선순위 큐로 스위핑할 때 크기가 가장 큰 순간의 크기가 정답
    */
    pq.push(arg_line[0].max_tan);
    int max_cross = 0;
    for (int i = 1; i < n; i++) {
        while (!pq.empty() && pq.top() < arg_line[i].min_tan) {
            pq.pop();
        }

        pq.push(arg_line[i].max_tan);
        max_cross = max<int>(max_cross, pq.size());
    }

    cout << max_cross;

    return 0;
}