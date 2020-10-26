#include"config.h"
#include<queue>

using namespace std;

int main()
{

}
/*
���� ���ͽ�Ʈ�� �˰����� ����Ұ�� �ҳ� ��Ҹ��� �ҹ漭 ���� ��ŭ �ؾߵ�
->��� �ҹ漭�� ���ÿ� ���ͽ�Ʈ�� �˰����� ����ϸ鼭 ���� �ذ�
->�ҹ漭 ���� 0�� ����ġ�� ���� ����
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