#include"config.h"

using namespace std;

int main()
{

}

int V, adj[200][200];


void solve()
{
	for (int i = 0; i < V; ++i)
		adj[i][i] = 0;

	for (int k = 0; k < V; ++k) {
		for (int i = 0; i < V; ++i)
			for (int j = 0; j < V; ++j) {
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
			}
	}
}
/*
이 도로가 추가되어야 하는지 여부는 쉽게 파악이 가능하나 추가하였을때 adj를 갱신해야 한다는 것을 생각하자
*/
bool update(int a, int b, int c)
{
	if (adj[a][b] <= c) return false;
	for (int x = 0; x < V; ++x)
		for (int y = 0; y < V; ++y)
			adj[x][y] = min(adj[x][y], min(adj[x][a] + c + adj[b][y], adj[x][b] + c + adj[a][y]));

	return true;
}