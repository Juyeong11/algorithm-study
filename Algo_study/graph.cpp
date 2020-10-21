#include"config.h"
#include"graph.h"





vector<vector<int>> adj;

int node_arr[] = {
		0,1,0,1,0,
		1,0,1,1,0,
		0,1,0,0,0,
		1,1,0,0,1,
		0,0,0,1,0
};
int w;
int h;

void graph_create()
{
	int factor_size = sizeof(node_arr) / sizeof(int);

	int quo = 1;
	while (factor_size / quo != quo && quo <= factor_size)
	{
		++quo;
	}
	w = quo;
	h = quo;


	for (int i = 0; i < w; ++i)
	{
		vector<int> a(0);
		adj.push_back(a);
		for (int j = 0; j < h; ++j)
		{
			adj[i].push_back(node_arr[i * 5 + j]);
		}
	}
}

vector<int> bfs(int start)
{
	vector<bool> discoverd(adj.size(), false);

	queue<int> q;

	vector<int> order;//방문순서

	discoverd[start] = true;
	q.push(start);

	while (!q.empty())
	{
		int here = q.front();
		q.pop();

		order.push_back(here);
		for (int there = 0; there < w; ++there)
		{
			if (adj[here][there] && !discoverd[there])
			{
				q.push(there);
				discoverd[there] = true;
			}
		}
	}
	return order;
}

//각 정점까지의 최단 거리와 너비 우선 탐색 스패닝 트리를 계산
void bfs2(int start, vector<int>& distance, vector<int>& parent)
{
	distance = vector<int>(adj.size(), -1);
	parent = vector<int>(adj.size(), -1);//parent[i] = t 이면 i의 부모 번호가 t

	queue<int> q;
	distance[start] = 0;
	parent[start] = start;
	q.push(start);
	while (!q.empty())
	{
		int here = q.front();
		q.pop();
		for (int there = 0; there<w;++there)
		{
			if (adj[here][there] && distance[there] == -1)
			{
				q.push(there);
				distance[there] = distance[here] + 1;
				parent[there] = here;
			}
		}
	}
}

vector<int> shortestPath(int v, const vector<int>& parent)
{
	vector<int> path(1, v);
	while (parent[v] != v)
	{
		v = parent[v];
		path.push_back(v);
	}
	reverse(path.begin(), path.end());
	return path;
}