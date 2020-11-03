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