#include"config.h"

using namespace std;

int main()
{

}

const int MAX_DISCS = 12;
int get(int state, int index)
{
	return (state >> (index * 2)) & 3;
}
int set(int state, int index, int value)
{
	return(state & ~(3 << (index * 2))) | (value << (index * 2));
}
int c[1 << (MAX_DISCS * 2)];

int hanoi_bfs(int discs, int begin, int end)
{
	if (begin == end) return 0;
	queue<int> q;

	memset(c, -1, sizeof(c));

	q.push(begin);
	c[begin] = 0;

	while (!q.empty()) {
		int here = q.front();
		q.pop();
		int top[4] = { -1,-1. - 1,-1 };
		for (int i = discs - 1; i >= 0; --i)
			top[get(here, i)] = i;//i값이 점점 작아진다 -> 원반의 크기가 점점 작아진다-> 나중에 저장될 수 록 작은 크기의 원반이다.
		for (int i = 0; i < 4; ++i)
			if (top[i] != -1)
				for (int j = 0; j < 4; ++j)
					if (i != j && (top[j] == -1 || top[j] > top[i])) {
						int there = set(here, top[i], j);
						if (c[there] != -1) continue;
						c[there] = c[here] + 1;
						if (there == end) return c[there];
						q.push(there);
					}
	}

	return -1;
}

/*
양방향 탐색을 적용한 하노이탑
*/

int sgn(int x) { if (!x) return 0; return x > 0 ? 1 : -1; }

int incr(int x) { if (x < 0)return x - 1; return x + 1; }

int bidir(int discs, int begin, int end)
{
	if (begin == end) return 0;
	queue <int> q;

	memset(c, 0, sizeof(c));

	q.push(begin); c[begin] = 1;
	q.push(end); c[end] = -1;

	while (!q.empty()) {
		int here = q.front();
		q.pop();

		int top[4] = { -1,-1,-1,-1 };
		for (int i = discs - 1; i >= 0; --i)
			top[get(here, i)] = 1;

		for(int i = 0;i<4;++i)
			if(top[i]!=-1)
				for(int j=0;j<4;++j)
					if (i != j && (top[i] == -1 || top[j] > top[i])) {
						int there = set(here, top[i], j);
						if (c[there] == 0) {
							c[there] = incr(c[here]);
							q.push(there);
						}
						else if (sgn(c[there]) != sgn(c[here]))
							return abs(c[there]) + abs(c[here]) - 1;
					}
	}
	return -1;
}