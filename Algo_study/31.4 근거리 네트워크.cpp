#include"config.h"

using namespace std;

int main()
{

}
/*
기존 건물이 연결되있는 경우 가중치를 0으로해 기존 컴포넌트들을 압축한다.
*/
const int MAX_V = 100;
int V;

vector<pair<int, int>> adj[MAX_V];


const int INF = numeric_limits<int>::max();

int prim(vector<pair<int, int>>& selected) {
	selected.clear();
	vector<bool> added(V, false);

	vector<int> minWeight(V, INF), parent(V, -1);//우선순위큐를 이용해서 구현할 수 있다.

	int ret = 0;

	minWeight[0] = parent[0] = 0;

	for (int iter = 0; iter < V; ++iter) {
		int u = -1;
		for (int v = 0; v < V; ++v)
			if (!added[v] && (u == -1 || minWeight[u] > minWeight[v]))
				u = v;

		if (parent[u] != u)
			selected.push_back(make_pair(parent[u], u));
		ret += minWeight[u];
		added[u] = true;

		for (int i = 0; i < adj[u].size(); ++i) {
			int v = adj[u][i].first, weight = adj[u][i].second;
			if (!added[v] && minWeight[v] > weight) {
				parent[v] = u;
				minWeight[v] = weight;
			}
		}
	}
	return ret;
}