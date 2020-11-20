#include"config.h"

using namespace std;
namespace Minimum_spanning {

	class DisjoinSet {
	private:
		vector<int> parent, rank;
	public:
		DisjoinSet(int n) : parent(n), rank(n, 1) {
			for (int i = 0; i < n; ++i)
				parent[i] = i;
		}
		int find(int u)
		{
			if (u == parent[u]) return u;
			return parent[u] = find(parent[u]);
		}
		void merge(int u, int v)
		{
			u = find(u); v = find(v);

			if (u == v) return;
			if (rank[u] > rank[v]) swap(u, v);

			parent[u] = v;
			if (rank[u] == rank[v]) ++rank[v];
		}
	};

	const int MAX_V = 100;
	int V;

	vector<pair<int, int>> adj[MAX_V];

	/*
	가중치가 최소인 정점들끼리 연결하면서 스패닝 트리를 완성한다
	사이클을 돌면 스패닝트리가 아니기 때문에 사이클을 확인해주는것이 핵심
	*/
	int kruskal(vector<pair<int, int>>& selected)
	{
		int ret = 0;
		selected.clear();//최소스패닝트리에 포함된 간선의 목록을 selected에 저장한다.
		vector<pair<int, pair<int, int>>> edges;
		for (int u = 0; u < V; ++u)
			for (int i = 0; i < adj[u].size(); ++i) {
				int v = adj[u][i].first, cost = adj[u][i].second;
				edges.push_back(make_pair(cost, make_pair(u, v)));
			}

		sort(edges.begin(), edges.end());

		DisjoinSet sets(V);//정점을 집합으로 나눈다 나눈 두 정점이 이미 같은 집합이라면 사이클을 도는것이다
		for (int i = 0; i < edges.size(); ++i) {
			int cost = edges[i].first;
			int u = edges[i].second.first, v = edges[i].second.second;
			if (sets.find(u) == sets.find(v)) continue;

			sets.merge(u, v);
			selected.push_back(make_pair(u, v));
			ret += cost;
		}
		return ret;
	}
	/*
	시작점부터 시작해 간선을 하나씩 추가하며 스패닝 트리가 될 때 까지 키워간다.
	*/
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
}
int main()
{

}