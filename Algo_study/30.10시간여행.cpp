#include"config.h"

using namespace std;

int main()
{

}
namespace time_traval {
	const int MAX_V = 100;
	int V;
	vector<pair<int, int>> adj[MAX_V];

	bool reachable[MAX_V][MAX_V];//한 정점에서 다른 정점으로 가는 경로의 존재 여부를 저장하는 배열

	int bellman(int src, int target)
	{
		vector<int> upper(V, INFINITY);
		upper[src] = 0;

		for (int iter = 0; iter < V - 1; ++iter)
			for (int here = 0; here < V; ++here)
				for (int i = 0; i < adj[here].size(); ++i) {
					int there = adj[here][i].first;
					int cost = adj[here][i].second;
					upper[there] = min(upper[there], upper[here] + cost);//iter 루프가 한번 돌때마다 upper[there]가 갱신된다
				}

		for (int here = 0; here < V; ++here)
			for (int i = 0; i < adj[here].size(); ++i) {
				int there = adj[here][i].first;
				int cost = adj[here][i].second;
				if (upper[here] + cost < upper[there])
					if (reachable[src][here] && reachable[here][target])
						return -INFINITY;
			}
		return upper[target];
	}
}