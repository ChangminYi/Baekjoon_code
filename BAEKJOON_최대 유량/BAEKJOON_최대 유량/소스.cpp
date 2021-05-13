//시간초과

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

#define SIZEOFALPHA 26

typedef class PIPE {
public:
	PIPE(): start(0), end(0), flowSize(0) {}
	PIPE(char _start, char _end, int _flowSize): flowSize(_flowSize) {
		if (_start > _end) { this->start = _end; this->end = _start; }
		else { this->start = _start; this->end = _end; }
	}
	char getStart() { return this->start; }
	char getEnd() { return this->end; }
	int getFlowSize() { return this->flowSize; }
	void setEnd(char _newEnd) { this->end = _newEnd; }
	void setFlowSize(int _newSize) { this->flowSize = _newSize; }
	bool operator< (PIPE &_P) {
		if (this->start == _P.start) { return this->end < _P.end; }
		else { return this->start < _P.start; }
	}
private:
	char start;
	char end;
	int flowSize;
}pipe;

int min(int a, int b) { return (a < b ? a : b); }

void mergeSerial(list<pipe> &arg) {
	for (list<pipe>::iterator i = arg.begin(); i != --arg.end(); i++) {
		list<pipe>::iterator j = i;
		j++;
		for (; j != arg.end(); j++) {
			pipe &pi = *i, &pj = *j;
			if (pi.getEnd() == pj.getStart()) {
				pi.setEnd(pj.getEnd());
				pi.setFlowSize(min(pi.getFlowSize(), pj.getFlowSize()));
				j = arg.erase(j);
				j--;
			}
		}
	}

}
void mergeParallel(list<pipe> &arg) {
	for (list<pipe>::iterator i = arg.begin(); i != --arg.end(); i++) {
		list<pipe>::iterator j = i; j++;
		pipe &pi = *i, &pj = *j;
		if (pi.getStart() == pj.getStart() && pi.getEnd() == pj.getEnd()) {
			pi.setFlowSize(pi.getFlowSize() + pj.getFlowSize());
			arg.erase(j);
		}
	}
}
void deleteNotLinked(list<pipe> &arg) {
	vector<pair<bool, bool>> check = vector<pair<bool, bool>>(SIZEOFALPHA, { true, true });
	for (int i = 1; i < SIZEOFALPHA - 1; i++) { check[i].first = false; check[i].second = false; }
	for (pipe &_p : arg) {
		check[_p.getStart() - 'A'].first = true;
		check[_p.getEnd() - 'A'].second = true;
	}

	for (list<pipe>::iterator i = arg.begin(); i != arg.end(); i++) {
		pipe &pi = *i;
		if (check[pi.getStart() - 'A'].first && check[pi.getStart() - 'A'].second) {
			if (check[pi.getEnd() - 'A'].first && check[pi.getEnd() - 'A'].second) {
				continue;
			}
			else {
				i = arg.erase(i);
				i--;
			}
		}
		else {
			i = arg.erase(i);
			i--;
		}
	}
}

int main() {
	cin.tie(NULL);
	cin.sync_with_stdio(false);

	int num = 0;
	cin >> num;

	list<pipe> set;
	for (int i = 0; i < num; i++) {
		char temp_c[2] = { 0 , 0 };
		int temp_i = 0;
		cin >> temp_c[0] >> temp_c[1] >> temp_i;
		set.push_back(pipe(temp_c[0], temp_c[1], temp_i));
	}

	while (set.size() != 1) {
		set.sort();
		mergeSerial(set);
		mergeParallel(set);
		deleteNotLinked(set);
	}

	cout << set.front().getFlowSize();

	return 0;
}