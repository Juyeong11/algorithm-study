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
				pq.push(make_pair(-nextDist, there));//우선순위 큐에 비교 연산자를 오버로딩 안하고-를 붙여 작은것이 먼저 나오도록 하였다.
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


namespace folyd {
	const int MAX_V = 100;
	int V;

	int adj[MAX_V][MAX_V];//i->j로 가는 간선 가중치
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
	C의 모든 값은 Ck-1에 의존하기 때문에 모든 값을 저장할 필요가 없다
	그리고 점화식에 사용되는 Ck(u,k)와 Ck-1(u,k)는 출발점이나 도착점이 k번 정점일 때 사용 가능한 경유점의 목록에 k가 추가되는 것이므로 아무런 의미가 없다.
	그래서 Ck와 Ck-1의 값을 구분하지 않고 섞어서 써도 됨을 알 수 있다.
	*/
	void f_floyd()
	{
		for (int i = 0; i < V; ++i) adj[i][i] = 0;

		for (int k = 0; k < V; ++k)
			for (int i = 0; i < V; ++i)
				for (int j = 0; j < V; ++j)
					adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
	}



	int via[MAX_V][MAX_V];//i, j까지 가는 최단경로가 경유하는 점중 가장 큰 점

	void floyd2()
	{
		for (int i = 0; i < V; ++i) adj[i][i] = 0;
		memset(via, -1, sizeof(via));

		for (int k = 0; k < V; ++k)
			for (int i = 0; i < V; ++i)
				for (int j = 0; j < V; ++j)
					if (adj[i][j] > adj[i][k] + adj[k][j]) {//i->j  i->k k->j 이런느낌
						via[i][j] = k;
						adj[i][j] = adj[i][k] + adj[k][j];
					}
	}

	void reconstruct(int u, int v, vector<int>& path)
	{
		if (via[u][v] == -1) {//중간에 연결된게 없다면
			path.push_back(u);
			if (u != v) path.push_back(v);
		}
		else {
			int w = via[u][v];
			reconstruct(u, w, path);
			path.pop_back();//w중복되니까 하나는 삭제 해준다
			reconstruct(w, v, path);
		}
	}
}
