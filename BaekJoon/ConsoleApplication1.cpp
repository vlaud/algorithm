#include <iostream>
#include <vector>
using namespace std;

class edge
{
public:
	int weight, from, to;
	edge(int weight, int from, int to) : weight(weight), from(from), to(to) {}

	bool operator< (const edge& other) const
	{
		weight < other.weight;
	}
};

void bellman(vector<edge>& edges,int s, int maxNode)
{
	int n = edges.size();
	vector<int> dist(maxNode+1, INT_MAX);
	dist[s] = 0;

	for (int i = 1; i < n; i++)
	{
		for (auto& e : edges)
		{
			int from = e.from;
			int weight = e.weight;
			int to = e.to;

			if (dist[from] != INT_MAX && dist[to] > dist[from] + weight)
			{
				dist[to] = dist[from] + weight;
			}
		}
	}

	for (auto& e : edges)
	{
		if (dist[e.from] != INT_MAX && dist[e.to] > dist[e.from] + e.weight)
		{
			cout << "음수 사이클 존재" << endl;
		}
	}
}
int main()
{
	vector<edge> edges;

	edges.emplace_back(edge(4, 1, 2));
	edges.emplace_back(edge(2, 1, 3));
	edges.emplace_back(edge(-3, 2, 3));
	edges.emplace_back(edge(1, 3, 4));
	bellman(edges, 1, 4);
	return 0;
}