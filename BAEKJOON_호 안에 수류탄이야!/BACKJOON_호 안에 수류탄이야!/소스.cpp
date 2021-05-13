#include <iostream>
#include <string>

std::string succ = "권병장님, 중대장님이 찾으십니다";
std::string fail = "엄마 나 전역 늦어질 것 같아";

int main() {
	int N = 0;
	std::cin >> N;

	int * const position = new int[N - 1];
	int destination = 0;
	int * const distance = new int[N - 1];

	for (int i = 0; i < N - 1; i++) {
		std::cin >> position[i];
	}
	std::cin >> destination;
	for (int i = 0; i < N - 1; i++) {
		std::cin >> distance[i];
	}

	int max_dist = 0;
	for (int i = 0; i < N - 1; i++) {
		if ((position[i] <= max_dist) && (position[i] + distance[i] > max_dist)) {
			max_dist = position[i] + distance[i];
		}
	}

	std::cout << ((max_dist >= destination ? succ : fail));
	return 0;
}