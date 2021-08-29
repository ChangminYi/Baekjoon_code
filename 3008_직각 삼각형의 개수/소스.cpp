#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long lli;
typedef pair<lli, lli> plli;

class point {
public:
	lli x = 0, y = 0;
	int plane = 0;

	point() {}
	point(lli _x, lli _y) : x(_x), y(_y) {}

	void rotate() {
		plane = (plane + 1) % 4;
		swap(x, y);
		y *= -1;
	}
	bool operator< (const point& other) const {
		return this->y * other.x < this->x * other.y;
	}
	bool operator== (const point& other) const {
		return this->x * other.y == this->y * other.x;
	}
};

int n;
lli ans = 0;
vector<plli> dir;
vector<point> p_list;
vector<lli> cnt(4);

istream& operator>> (istream& in, plli& p) {
	return in >> p.first >> p.second;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);

	cin >> n;
	dir = vector<plli>(n);
	for (plli& p : dir) {
		cin >> p;
	}

	for (int i = 0; i < n; i++) {
		p_list.clear();

		for (int j = 0; j < n;j++) {
			if (i != j) {
				point tmp = point(dir[j].first - dir[i].first, dir[j].second - dir[i].second);
				while (tmp.x <= 0 || tmp.y < 0) {
					tmp.rotate();
				}

				p_list.push_back(tmp);
			}
		}

		sort(p_list.begin(), p_list.end());
		for (int j = 0, k; j < (int)p_list.size(); j = k) {
			fill(cnt.begin(), cnt.end(), 0);
			
			for (k = j; (k < (int)p_list.size()) && (p_list[j] == p_list[k]); k++) {
				cnt[p_list[k].plane]++;
			}
			
			for (int k = 0; k < (int)cnt.size(); k++) {
				ans += cnt[k] * cnt[(k + 1) % cnt.size()];
			}
		}
	}

	cout << ans;

	return 0;
}