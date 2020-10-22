/*
나머지 연산 분배 법칙

((c%n)*10+x)%n == (c*10+x)%n

c를 n으로 나눈 나머지의 앞에 x를 추가해 n으로 나눈 나머지값과
c의 앞에 x를 추가해 n으로 나눈 나머지 값은 같다.

c를 앞에서 부터 만들어 갈때 지금까지 만든 c의 뒤에 숫자 x를 붙인 결과인 c*10+x를 n으로 나눈 나머지는 c를 모르더라도 알 수 있다.



이 문제를 푸는 한가지 방법은 c를 n으로 나눈 나머지를 정점으로 표현한 방향그래프를 만들어 보는 것 입니다.
따라서 그래프에는 0n-1까지의 나머지를 표현하는 n개의 정점이 있게 됩니다.

정점a는 현재까지 만든 c를 n으로 나눈 나머지가 a인 상태를 나타낸다

c의 뒤에 숫자 x를 붙이면 나머지는 a*10+x) % n 으로 바뀐다
따라서 두 정점을 간선으로 연결하되, 이간선을  x로 번호를 매기도록 합니다.

간선을 하나 따라갈 때마다 c에 한 자리를 추가하게 됩니다. 이 최단 경로의 간선의 번호를 모으면 가장 짧은 c를 찾을 수 있음은 분명하다.
하지만 경로가 짧다고 해서 정답이 아니다 같은 길이의 경우는 간선의 번호가 사전순으로 앞에오는 경로가 가장 짧은 경로가 된다.


너비우선 탐색이 각 정점을 방문할 때마다 인접한 간선을 임의의 순서 대신 번호가 증가하는 순서로 검사하는 것->맞네 쉽네

시작점으로부터의 거리를 기준으로 분류하자 H 거리가i인 정점의 집합을 Hi라고 쓰자

이제 마지막 조건인 결과값이 n+m이상 이여야한다는 조건을 생각해보자
이 조건을 지키기 위해서 그래프를 한바퀴 돌아오는 경로를 찾아야만 합니다.

1번 조건을 고려했을 때, 시작점인 0과 그래프를 한 바퀴 돌아서 다시 도착한 0은 같은 정점일 수 없다는 사실입니다.
*/
#include"config.h"

using namespace std;

int main()
{

}

int append(int here, int edge, int mod)
{
	int there = here * 10 + edge;
	if (there >= mod) return mod + there % mod;
	return there % mod;
}

string gifts(string digits, int n, int m)
{
	//사용가능한 숫자 목록t(digits.begin(), digits.end());

	vector<int> parent(2 * n, -1), choice(2 * n, -1);
	queue <int> q;

	parent[0] = 0;
	q.push(0);
	while (!q.empty()) {
		int here = q.front();
		q.pop();
		for (int i = 0; i < digits.size(); ++i) {
			int there = append(here, digits[i] - '0', n);
			if (parent[there] == -1) {
				parent[there] = here;
				choice[there] = digits[i] - '0';
				q.push(there);
			}
		}
	}

	if (parent[n + m] == -1) return "IMPOSSIBLE";

	string ret;
	int here = n + m;
	while (parent[here] != here) {
		ret += char('0' + choice[here]);
		here = parent[here];
	}
	reverse(ret.begin(), ret.end());
	return ret;
}
