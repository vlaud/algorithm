#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define INF 0x3f3f3f3f

typedef pair<int, int> iPair;

class Graph {
	int V;
	vector<iPair>* adj;

public:
	Graph(int V);
	void addEdge(int u, int v, int w);
	void shortestPath(int s);
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new vector<iPair>[V];
}

void Graph::addEdge(int u, int v, int w)
{
	adj[u].push_back(make_pair(v, w));
	adj[v].push_back(make_pair(u, w));
}

void Graph::shortestPath(int s)
{
	priority_queue<iPair, vector<iPair>, greater<iPair>> pq;

	vector<int> dist(V, INF);

	pq.push(make_pair(0, s));
	dist[s] = 0;

	while (!pq.empty()) {
		int u = pq.top().second;
		pq.pop();

		for (auto n : adj[u]) {
			int v = n.first;
			int w = n.second;

			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				pq.push(make_pair(dist[v], v));
			}
		}
	}

	// Print the shortest distances
	cout << "Vertex Distance from Source" << endl;
	for (int i = 0; i < V; ++i)
		cout << i << " \t\t " << dist[i] << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int V = 9; // Number of vertices
	Graph g(V);

	// Add edges to the graph
	g.addEdge(0, 1, 4);
	g.addEdge(0, 7, 8);
	g.addEdge(1, 2, 8);
	g.addEdge(1, 7, 11);
	g.addEdge(2, 3, 7);
	g.addEdge(2, 8, 2);
	g.addEdge(2, 5, 4);
	g.addEdge(3, 4, 9);
	g.addEdge(3, 5, 14);
	g.addEdge(4, 5, 10);
	g.addEdge(5, 6, 2);
	g.addEdge(6, 7, 1);
	g.addEdge(6, 8, 6);
	g.addEdge(7, 8, 7);

	// Call the shortestPath function
	g.shortestPath(0);

	return 0;
}


