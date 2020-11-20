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
	����ġ�� �ּ��� �����鳢�� �����ϸ鼭 ���д� Ʈ���� �ϼ��Ѵ�
	����Ŭ�� ���� ���д�Ʈ���� �ƴϱ� ������ ����Ŭ�� Ȯ�����ִ°��� �ٽ�
	*/
	int kruskal(vector<pair<int, int>>& selected)
	{
		int ret = 0;
		selected.clear();//�ּҽ��д�Ʈ���� ���Ե� ������ ����� selected�� �����Ѵ�.
		vector<pair<int, pair<int, int>>> edges;
		for (int u = 0; u < V; ++u)
			for (int i = 0; i < adj[u].size(); ++i) {
				int v = adj[u][i].first, cost = adj[u][i].second;
				edges.push_back(make_pair(cost, make_pair(u, v)));
			}

		sort(edges.begin(), edges.end());

		DisjoinSet sets(V);//������ �������� ������ ���� �� ������ �̹� ���� �����̶�� ����Ŭ�� ���°��̴�
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
	���������� ������ ������ �ϳ��� �߰��ϸ� ���д� Ʈ���� �� �� ���� Ű������.
	*/
	const int INF = numeric_limits<int>::max();

	int prim(vector<pair<int, int>>& selected) {
		selected.clear();
		vector<bool> added(V, false);

		vector<int> minWeight(V, INF), parent(V, -1);//�켱����ť�� �̿��ؼ� ������ �� �ִ�.

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