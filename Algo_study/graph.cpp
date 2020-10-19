#include"config.h"
#include"graph.h"


void create(vector<vector<int>> adj, int factor[], int factor_size)
{
	int quo = 1;
	while (factor_size / quo != quo && quo <= factor_size)
	{
		++quo;
	}
	const int w = quo;
	const int h = quo;


	for (int i = 0; i < w; ++i)
	{
		vector<int> a(0);
		adj.push_back(a);
		for (int j = 0; j < h; ++j)
		{
			adj[i].push_back(factor[i * 5 + j]);
		}
	}

	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < h; ++j)
		{
			cout << adj[i][j] << " ";
		}
		cout << endl;
	}
}