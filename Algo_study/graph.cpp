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

	vector<int> order;//�湮����

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

//�� ���������� �ִ� �Ÿ��� �ʺ� �켱 Ž�� ���д� Ʈ���� ���
void bfs2(int start, vector<int>& distance, vector<int>& parent)
{
	distance = vector<int>(adj.size(), -1);
	parent = vector<int>(adj.size(), -1);//parent[i] = t �̸� i�� �θ� ��ȣ�� t

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

int V_dij;

const int MAX_V_dij = 100;
vector<pair<int, int>> adj_dij[MAX_V_dij];

vector<int> dijkstra(int src)
{
	vector<int> dist(V_dij, INFINITY);
	dist[src] = 0;

	priority_queue<pair<int, int>> pq;
	pq.push(make_pair(0, src));
	while (!pq.empty()) {
		int cost = -pq.top().first;
		int here = pq.top().second;
		pq.pop();

		if (dist[here] < cost) continue;

		for (int i = 0; i < adj_dij[here].size(); ++i) {
			int there = adj_dij[here][i].first;
			int nextDist = cost + adj_dij[here][i].second;
			if (dist[there] > nextDist) {
				dist[there] = nextDist;
				pq.push(make_pair(-nextDist, there));//�켱���� ť�� �� �����ڸ� �����ε� ���ϰ�-�� �ٿ� �������� ���� �������� �Ͽ���.
			}
		}
	}

	return dist;
}

int bf_V;

vector<pair<int, int>> bf_adj[400];

vector<int> bellmanford(int src)
{
	vector<int> upper(bf_V, INFINITY);
	upper[src] = 0;
	bool updated;

	for (int iter = 0; iter < bf_V; ++iter) {
		updated = false;
		for (int here = 0; here < bf_V; ++here)
			for (int i = 0; i < bf_adj[here].size(); ++i) {
				int there = bf_adj[here][i].first;
				int cost = bf_adj[here][i].second;
				if (upper[there] > upper[here] + cost) {//�̰� �ᱹ ���� ª�� �Ÿ��� ����� ������ ã�� ���� ���ݾ� ���ͽ�Ʈ��� ���� ����Ѱ� �ƴѰ�??
					upper[there] = upper[here] + cost;
					updated = true;
				}
			}
		if (!updated)break;
	}
	if (updated) upper.clear();//v��° ��ȸ������ ��ȭ�� �����ߴٸ� ���� ����Ŭ�� �ִ�.
	return upper;
}


namespace folyd {
	const int MAX_V = 100;
	int V;

	int adj[MAX_V][MAX_V];//i->j�� ���� ���� ����ġ
	int C[MAX_V][MAX_V][MAX_V];

	void allPairShortestPath1()
	{
		for (int i = 0; i < V; ++i)
			for (int j = 0; j < V; ++j)
				if (i != j)
					C[0][i][j] = min(adj[i][j], adj[i][0] + adj[0][j]);
				else
					C[0][i][j] = 0;

		for (int k = 1; k < V; ++k)
			for (int i = 0; i < V; ++i)
				for (int j = 0; j < V; ++j)
					C[k][i][j] = min(C[k - 1][i][j], C[k - 1][i][k] + C[k - 1][k][j]);
	}
	/*
	C�� ��� ���� Ck-1�� �����ϱ� ������ ��� ���� ������ �ʿ䰡 ����
	�׸��� ��ȭ�Ŀ� ���Ǵ� Ck(u,k)�� Ck-1(u,k)�� ������̳� �������� k�� ������ �� ��� ������ �������� ��Ͽ� k�� �߰��Ǵ� ���̹Ƿ� �ƹ��� �ǹ̰� ����.
	�׷��� Ck�� Ck-1�� ���� �������� �ʰ� ��� �ᵵ ���� �� �� �ִ�.
	*/
	void f_floyd()
	{
		for (int i = 0; i < V; ++i) adj[i][i] = 0;

		for (int k = 0; k < V; ++k)
			for (int i = 0; i < V; ++i)
				for (int j = 0; j < V; ++j)
					adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
	}



	int via[MAX_V][MAX_V];//i, j���� ���� �ִܰ�ΰ� �����ϴ� ���� ���� ū ��

	void floyd2()
	{
		for (int i = 0; i < V; ++i) adj[i][i] = 0;
		memset(via, -1, sizeof(via));

		for (int k = 0; k < V; ++k)
			for (int i = 0; i < V; ++i)
				for (int j = 0; j < V; ++j)
					if (adj[i][j] > adj[i][k] + adj[k][j]) {//i->j  i->k k->j �̷�����
						via[i][j] = k;
						adj[i][j] = adj[i][k] + adj[k][j];
					}
	}

	void reconstruct(int u, int v, vector<int>& path)
	{
		if (via[u][v] == -1) {//�߰��� ����Ȱ� ���ٸ�
			path.push_back(u);
			if (u != v) path.push_back(v);
		}
		else {
			int w = via[u][v];
			reconstruct(u, w, path);
			path.pop_back();//w�ߺ��Ǵϱ� �ϳ��� ���� ���ش�
			reconstruct(w, v, path);
		}
	}
}
