/*
�ִܰ�� ������ Ǯ �ٸ� Ž�� �˰����� �˾ƺ���
*/

#include"config.h"
#include<map>
using namespace std;

int main()
{

}
/*
* 15-���� ����	`
*/
class State {//��Ʈ����ũ�� �̿��� 0~15�����ǰ��� 64��Ʈ ���� �ϳ��� �����غ���
public:
	vector<State> getAdjacent()const {/**/};

	bool operator < (const State& rhs) const {/**/ };

	bool operator == (const State& rhs) const {/**/};
};

typedef map<State, int> StateMap;

int puzzle_bfs(State start, State finish)
{
	if (start == finish) return 0;

	StateMap c;

	queue<State> q;
	q.push(start);
	c[start] = 0;
	while (!q.empty()) {
		State here = q.front();
		q.pop();
		int cost = c[here];

		vector<State> adjacent = here.getAdjacent();
		for (int i = 0; i < adjacent.size(); ++i) {
			if (c.count(adjacent[i]) == 0) {
				if (adjacent[i] == finish) return cost + 1;
				c[adjacent[i]] = cost + 1;
				q.push(adjacent[i]);
			}
		}
	}
	return -1;
}
/*
����� Ž��
���� �������� �����ϴ� ������ Ž�� - ��ǥ�������� ������ �Ųٷ� �ö���� ������ Ž��
-> ���� ������� ������ ����

�ʺ� �켱 Ž���� ���� �ٸ��� �ʴ�. -> ������� ������ Ž������ �湮�� �������� ��� ���� ť�� �ְ� ��ȣ�� �ٲ� �����Ѵ�.
*/

int sgn(int x) { if (!x) return 0; return x > 0 ? 1 : -1; }

int incr(int x) { if (x < 0) return x - 1; return x + 1; }

int bidirectional(State start, State finsh)
{
	StateMap c;

	queue<State> q;

	if (start == finsh) return 0;

	q.push(start); c[start] = 1;

	q.push(finsh); c[finsh] = -1;

	while (!q.empty()) {
		State here = q.front();
		q.pop();

		vector<State> adjacent = here.getAdjacent();
		for (int i = 0; i < adjacent.size(); ++i) {
			StateMap::iterator it = c.find(adjacent[i]);//��ã���� c.end()�� ��ȯ�Ѵ�.
			if (it == c.end()) {
				c[adjacent[i]] = incr(c[here]);
				q.push(adjacent[i]);
			}
			else if (sgn(it->second) != sgn(c[here]))
				return abs(it->second) + abs(c[here]) - 1;
		}
	}
	return -1;
}

/*
����� Ž�������� �湮�ϴ� �������� �ִ� �Ÿ��� ���� ���������� �����Ѵ�.
���� �Ը� ū Ž�� ������ Ǯ���� �ᱹ �ٸ� ����� �ʿ��ϴ�-> ���� �켱 Ž��

- ���� ���� ã�� ������ �ִܰŸ����� Ȯ���� ���Ѵ�.
- ������ �湮�ߴ��� Ȯ���� ���Ѵ�.->����Ŭ�� �� �� ���ִ�.
->���̸� ������ �� �������� �ذ� �� ��� --> ����������� ������� Ž��
*/

int best;//���� ���� ã�� �ִܰŸ��� ���� ������ �θ� ���� Ž�� ���̰� �� �ͺ��� ������� Ž���� ���� ������ �� �ִ�.

void dfs(State here, const State& finish, int steps)
{
	if (steps >= best) return;

	if (here == finish) { best = steps; return; }

	vector<State> adjacent = here.getAdjacent();
	for (int i = 0; i < adjacent.size(); ++i)
		dfs(adjacent[i], finish, steps + 1);
}

int ids(State start, State finish, int growthStep)
{
	for (int limit = 4; ; limit += growthStep) {
		best = limit + 1;
		dfs(start, finish, 0);
		if (best <= limit) return best;
	}
	return -1;

}