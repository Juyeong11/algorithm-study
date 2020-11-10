#include"config.h"
#include<queue>

using namespace std;

int main()
{

}
/*
기존 다익스트라 알고리즘을 사용할경우 불난 장소마다 소방서 갯수 만큼 해야됨
->모든 소방서를 동시에 다익스트라 알고리즘을 사용하면서 문제 해결
->소방서 끼리 0인 가중치의 간선 연결
*/
int V;
const int MAX_V = 1000;
vector<pair<int, int>> adj[MAX_V];

int fireTruck_dijkstra(int src,int arrival)
{
	vector<int> dist(V, INFINITY);
	dist[src] = 0;

	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, src));

	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		for (int i = 0; i < adj[here].size(); ++i) {
			int there = adj[here][i].first;
			int nextDist = cost + adj[here][i].second;

			if (there == arrival) return nextDist;

			if (dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));
			}
		}
	}
	return -1;

}