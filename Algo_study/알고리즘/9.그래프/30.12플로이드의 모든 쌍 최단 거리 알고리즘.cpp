#include"config.h"

using namespace std;

int main()
{

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
