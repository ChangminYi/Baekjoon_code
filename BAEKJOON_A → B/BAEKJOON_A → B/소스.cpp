//오버플로우 조심!

#include <iostream>
#include <queue>

using namespace std;

typedef class NODE {
public:
	unsigned long long number;
	int count;
	NODE() : number(0), count(0) {};
	NODE(int _number, int _count) : number(_number), count(_count) {};
}node;

int main() {
	unsigned long long A = 0, B = 0;
	std::cin >> A >> B;

	int cnt = -1;
	queue<node> q;
	q.push(node(A, 1));
	while (!q.empty()) {
		node cur = q.front();
		q.pop();

		if (cur.number == B) {
			cnt = cur.count;
			break;
		}
		else {
			if (cur.number * 10 + 1 <= B) {
				q.push(node(cur.number * 10 + 1, cur.count + 1));
			}
			if (cur.number * 2 <= B) {
				q.push(node(cur.number * 2, cur.count + 1));
			}
		}
	}
	std::cout << cnt;

	return 0;
}