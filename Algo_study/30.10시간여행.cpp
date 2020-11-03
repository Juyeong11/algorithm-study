#include"config.h"

using namespace std;

int main()
{

}
namespace time_traval {
	const int MAX_V = 100;
	int V;
	vector<pair<int, int>> adj[MAX_V];

	bool reachable[MAX_V][MAX_V];//�� �������� �ٸ� �������� ���� ����� ���� ���θ� �����ϴ� �迭

	int bellman(int src, int target)
	{
		vector<int> upper(V, INFINITY);
		upper[src] = 0;

		for (int iter = 0; iter < V - 1; ++iter)
			for (int here = 0; here < V; ++here)
				for (int i = 0; i < adj[here].size(); ++i) {
					int there = adj[here][i].first;
					int cost = adj[here][i].second;
					upper[there] = min(upper[there], upper[here] + cost);//iter ������ �ѹ� �������� upper[there]�� ���ŵȴ�
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