#include"config.h"

using namespace std;

int main()
{

}

/*
u->v = u->x + x->v �� ��ȭ���� �����ϴµ� x�� ���� ���Ƿ� �����־ ����� ���ٴ� ����� �̿����� -> x�� �ܼӿ� �ɸ��� �ð� ���� �����Ѵ�.
*/
int V, adj[500][500];

int delay[500];
int W[500][500];

void solve()
{
	vector<pair<int, int>> order;
	for (int i = 0; i < V; ++i) order.push_back(make_pair(delay[i], i));
	sort(order.begin(), order.end());

	for (int i = 0; i < V; ++i)
		for (int j = 0; j < V; ++j)
			if (i == j)
				W[i][j] = 0;
			else
				W[i][j] = adj[i][j];

	int ret = INFINITY;
	for (int k = 0; k < V; ++k) {
		int w = order[k].second;
		for(int i=0;i<V;++i)
			for (int j = 0; j < V; ++j) {
				adj[i][j] = min(adj[i][j], adj[i][w] + adj[w][j]);
				W[i][j] = min(adj[i][w] + delay[w] + adj[w][j], W[i][j]);
			}
	}
}