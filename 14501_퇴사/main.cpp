#include <iostream>
#include <vector>

typedef struct _NODE {
	int T, P;
	bool canDo;
	std::vector<_NODE *> adj;
} node;

int findMax(const node *n) {
	if (n->canDo == false) {
		return 0;
	}
	else if (n->adj.empty()) {
		return n->P;
	}
	else {
		int max = 0, temp = 0;
		for (int i = 0; i < n->adj.size(); i++) {
			temp = findMax(n->adj.at(i));
			if (max < temp) {
				max = temp;
			}
		}

		return n->P + max;
	}
}

int main() {
	int day = 0;
	std::cin >> day;
	node *s = new node[day];
	for (int i = 0; i < day; i++) {
		std::cin >> s[i].T >> s[i].P;
		s[i].canDo = ((s[i].T + i > day) ? false : true);
	}
	for (int i = 0; i < day; i++) {
		for (int j = i + 1; j < day; j++) {
			if ((s[j].canDo == true) && (i + s[i].T <= j)) {
				s[i].adj.push_back(s + j);
			}
		}
	}

	int max_P = 0, temp = 0;
	for (int i = 0; i < day; i++) {
		max_P = ((max_P < (temp = findMax(s + i))) ? temp : max_P);
	}

	std::cout << max_P;
	delete[] s;
	return 0;
}