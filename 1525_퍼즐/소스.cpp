#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <unordered_set>

using namespace std;

typedef pair<int, int> pint;
typedef pair<string, int> node;

const string goal = "123456780";
const vector<pint> poss_dir = {
	make_pair(0, 1),
	make_pair(0, -1),
	make_pair(1, 0),
	make_pair(-1, 0)
};

string puzzle;
unordered_set<string> visit;
queue<node> que;

pint operator+(const pint& lhs, const pint& rhs) {
	return pint(lhs.first + rhs.first, lhs.second + rhs.second);
}

bool in_range(const pint& p) {
	return (0 <= p.first && p.first < 3) && (0 <= p.second && p.second < 3);
}

int bfs() {
	visit.insert(puzzle);
	que.push(node(puzzle, 0));

	while (!que.empty()) {
		node cur = que.front();
		que.pop();

		if (cur.first == goal) {
			return cur.second;
		}
		else {
			int empty_idx = cur.first.find('0');
			pint cur_dir = pint(empty_idx / 3, empty_idx % 3);
			
			for (const pint& dir : poss_dir) {
				pint nxt = cur_dir + dir;
				string nxt_puzzle = cur.first;

				if (in_range(nxt)) {
					swap(nxt_puzzle[3 * cur_dir.first + cur_dir.second], nxt_puzzle[3 * nxt.first + nxt.second]);

					if (visit.find(nxt_puzzle) == visit.end()) {
						visit.insert(nxt_puzzle);
						que.push(node(nxt_puzzle, cur.second + 1));
					}
				}
			}
		}
	}

	return -1;
}

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	cout.tie(nullptr)->sync_with_stdio(false);
	
	for (int i = 0; i < 9; i++) {
		char tmp;
		cin >> tmp;
		puzzle.push_back(tmp);
	}

	cout << bfs();

	return 0;
}