#include <iostream>
#include <queue>

using namespace std;

bool visit[1000001] = { false };

typedef struct NODE {
	int height, moveCount;
}node;

int main() {
	int maxHeight = 0, start = 0, dest = 0, up = 0, down = 0;
	cin >> maxHeight >> start >> dest >> up >> down;
	
	queue<node> toGo;

	toGo.push({ start, 0 });
	while (!toGo.empty()) {
		node current = toGo.front();
		toGo.pop();

		if (current.height == dest) {
			cout << current.moveCount;
			return 0;
		}
		else {
			if (!visit[current.height]) {
				visit[current.height] = true;

				if (current.height + up <= maxHeight && !visit[current.height + up]) {
					toGo.push({ current.height + up, current.moveCount + 1 });
				}
				if (current.height - down >= 1 && !visit[current.height - down]) {
					toGo.push({ current.height - down, current.moveCount + 1 });
				}
			}
		}
	}

	cout << "use the stairs";

	return 0;
}