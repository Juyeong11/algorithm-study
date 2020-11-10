#include"config.h"
#include"graph.h"
using namespace std;

int main()
{

}
int V;

vector<pair<int, int>> adj[410];
const int START = 401;

vector<int> NTHLON_problem_dijkstra(int src)
{
	vector<int> dist(V, INFINITY);
	dist[src] = 0;

	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, src));
	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		if (dist[here] < cost) continue;

		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			int nextDist = cost + adj[here][i].second;
			if (dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));//우선순위 큐에 비교 연산자를 오버로딩 안하고-를 붙여 작은것이 먼저 나오도록 하였다.
			}
		}
	}

	return dist;
}



int vertex(int delta)
{
	return delta + 200;
}

int solve(const vector<int>& a, const vector<int>& b)
{
	V = 402;
	for (int i = 0; i < V; ++i) adj[i].clear();
	for (int i = 0; i < a.size(); ++i) {
		int delta = a[i] - b[i];
		adj[START].push_back(make_pair(vertex(delta), a[i]));
	}

	for (int delta = -200; delta <= 200; ++delta) {
		for (int i = 0; i < a.size(); ++i) {//i번 종목을 뒤로 붙인다????
			int next = delta + a[i] - b[i];//차이가 -1,-2,-3.....-200....-400
										   //차이가 201, 200, 199, 198... 0, ...-200인점
			if (abs(next) > 200) continue;
			adj[vertex(delta)].push_back(make_pair(vertex(next), a[i]));//vertex(delta)번그래프에 연결된 정점들
		}
	}
	vector<int> shortest = NTHLON_problem_dijkstra(START);
	int ret = shortest[vertex(0)];
	if (ret == INFINITY) return -1;
	return ret;
}

int bf_V;

vector<pair<int, int>> bf_adj[400];

vector<int> bellmanford(int src)
{
	vector<int> upper(bf_V, INFINITY);
	upper[src] = 0;
	bool updated;

	for (int iter = 0; iter < V; ++iter) {
		updated = false;
		for (int here = 0; here < V; ++here) 
			for (int i = 0; i < bf_adj[here].size(); ++i) {
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
				if (upper[there] > upper[here] + cost) {//이게 결국 가장 짧은 거리로 연결된 정점을 찾아 가는 거잖아 다익스트라랑 거의 비슷한거 아닌가??
					upper[there] = upper[here] + cost;
					updated = true;
				}
			}
		if (!updated)break;
		
	}
	if (updated) upper.clear();//v번째 순회에서도 완화가 성공했다면 음수 사이클이 있다.
	return upper;
}