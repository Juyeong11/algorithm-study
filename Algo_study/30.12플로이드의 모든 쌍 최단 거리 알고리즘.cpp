#include"config.h"

using namespace std;

int main()
{

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
