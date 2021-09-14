#include <iostream>
#include <cmath>

using namespace std;

typedef long long lli;

struct pos {
    lli x, y;
    pos(lli x = 0, lli y = 0) :x(x), y(y) {}
    pos operator-(pos rhs) {
        return pos(this->x - rhs.x, this->y - rhs.y);
    }
};

int testcase;
lli x_1, x_2, y_1, y_2;
pos line[2], rect[4];

int ccw(pos a, pos b) {
    lli tmp = a.x * b.y - a.y * b.x;
    return (tmp == 0 ? 0 : (tmp > 0 ? 1 : -1));
}

int ccw(pos a, pos b, pos c) {
    return ccw(b - a, c - a);
}

bool is_cross(pos a, pos b, pos c, pos d) {
    if (ccw(a, b, c) * ccw(a, b, d) <= 0 && ccw(c, d, a) * ccw(c, d, b) <= 0) {
        if ((a.x < c.x && a.x < d.x && b.x < c.x && b.x < d.x)
            || (c.x < a.x && c.x < b.x && d.x < a.x && d.x < b.x)) {
            return false;
        }
        else if ((a.y < c.y && a.y < d.y && b.y < c.y && b.y < d.y)
            || (c.y < a.y && c.y < b.y && d.y < a.y && d.y < b.y)) {
            return false;
        }
        else {
            return true;
        }
    }
    else {
        return false;
    }
}

bool in_rect(pos p) {
    if (rect[0].x <= p.x && p.x <= rect[3].x) {
        if (rect[0].y <= p.y && p.y <= rect[3].y) {
            return true;
        }
    }
    return false;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.tie(nullptr)->sync_with_stdio(false);

    cin >> testcase;
    do {
        for (int i = 0; i < 2; i++) {
            cin >> line[i].x >> line[i].y;
        }
        cin >> x_1 >> y_1 >> x_2 >> y_2;
        lli min_x = min(x_1, x_2), max_x = max(x_1, x_2);
        lli min_y = min(y_1, y_2), max_y = max(y_1, y_2);

        rect[0] = pos(min_x, min_y);
        rect[1] = pos(min_x, max_y);
        rect[2] = pos(max_x, min_y);
        rect[3] = pos(max_x, max_y);

        if (in_rect(line[0]) && in_rect(line[1])) {
            cout << 'T';
        }
        else {
            if (is_cross(rect[0], rect[2], line[0], line[1])
                || is_cross(rect[0], rect[3], line[0], line[1])
                || is_cross(rect[1], rect[2], line[0], line[1])
                || is_cross(rect[1], rect[3], line[0], line[1])) {
                cout << 'T';
            }
            else {
                cout << 'F';
            }
        }
        cout << '\n';
    } while (--testcase > 0);

    return 0;
}