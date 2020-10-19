#include"config.h"
#include"graph.h"

int main()
{
	vector<vector<int>> adj;

	int graph_f[] = {
		0,2,0,0,0,
		0,0,3,0,0,
		0,0,0,0,0,
		0,0,0,0,0,
		0,0,0,0,0
	};
	create(adj, graph_f, sizeof(graph_f) / sizeof(int));

	return 0;
}

