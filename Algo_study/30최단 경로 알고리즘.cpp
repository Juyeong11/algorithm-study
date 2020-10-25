#include"config.h"
#include<queue>
using namespace std;

int main()
{

}

int V;

const int MAX_V = 100;
vector<pair<int, int>> adj[MAX_V];

vector<int> dijkstra(int src)
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
				pq.push(make_pair(-nextDist, there));//�켱���� ť�� �� �����ڸ� �����ε� ���ϰ�-�� �ٿ� �������� ���� �������� �Ͽ���.
			}
		}
	}

	return dist;
}