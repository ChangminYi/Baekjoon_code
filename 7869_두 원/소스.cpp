#include <iostream>
#include <cmath>

using namespace std;

const double pi = 3.14159265358979;

double x_1, y_1, r_1;
double x_2, y_2, r_2;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> x_1 >> y_1 >> r_1 >> x_2 >> y_2 >> r_2;

    (cout << fixed).precision(3);
    double dist = sqrt((x_1 - x_2) * (x_1 - x_2) + (y_1 - y_2) * (y_1 - y_2));
    /*
    * �� ���� ������ �ʴ� ���, �� ���� �κ������� ��ġ�� ���, �� ���� �ٸ� �� �ȿ� �ִ� ���
    * �� 3������ ��찡 �����ϴ�. ��쿡 ���� ����� �����ְ�,
    * �κ������� ������ ���� �ﰢ�� 2���� �����Ͽ� ����ϸ� �ȴ�.
    */
    if (dist >= r_1 + r_2) {
        // ��� ����. 0�� ����ϸ� int�� �ν�.
        cout << 0.0;
    }
    else if (dist <= abs(r_1 - r_2)) {
        cout << pow(min(r_1, r_2), 2) * pi;
    }
    else {
        double t1 = acos((r_1 * r_1 + dist * dist - r_2 * r_2) / (2 * r_1 * dist));
        double t2 = acos((r_2 * r_2 + dist * dist - r_1 * r_1) / (2 * r_2 * dist));

        double a1 = ((2 * r_1 * r_1 * t1) - (r_1 * r_1 * sin(2 * t1))) / 2;
        double a2 = ((2 * r_2 * r_2 * t2) - (r_2 * r_2 * sin(2 * t2))) / 2;

        cout << a1 + a2;
    }

    return 0;
}