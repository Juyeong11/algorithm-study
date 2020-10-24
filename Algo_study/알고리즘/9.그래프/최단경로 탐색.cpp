/*
최단경로 문제를 풀 다른 탐색 알고리즘을 알아보자
*/

#include"config.h"
#include<map>
using namespace std;

int main()
{

}
/*
* 15-퍼즐 예제	`
*/
class State {//비트마스크를 이용해 0~15까지의값을 64비트 정수 하나에 저장해보자
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
양방향 탐색
시작 정점에서 시작하는 정방향 탐색 - 목표정점에서 시작해 거꾸로 올라오는 역방향 탐색
-> 둘이 가운데에서 만나면 종료

너비 우선 탐색과 거의 다르지 않다. -> 정방향과 역방향 탐색에서 방문할 정점들을 모두 같은 큐에 넣고 부호를 바꿔 구별한다.
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
			StateMap::iterator it = c.find(adjacent[i]);//못찾으면 c.end()를 반환한다.
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
양방향 탐색에서도 방문하는 정점수는 최단 거리에 따라 지수적으로 증가한다.
따라서 규모가 큰 탐색 문제를 풀때는 결국 다른 방법이 필요하다-> 깊이 우선 탐색

- 지금 까지 찾은 정점이 최단거리인지 확신을 못한다.
- 정점을 방문했는지 확인을 안한다.->사이클을 돌 수 도있다.
->깊이를 제한해 두 문제점을 해결 한 방법 --> 점점깊어지는 깊어지는 탐색
*/

int best;//지금 까지 찾은 최단거리를 전역 변수에 두면 현재 탐색 깊이가 이 것보다 길어지면 탐색을 조기 종료할 수 있다.

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