#include "../GraphBase/Graph.cpp"
#include <vector>
//#include <queue>

using namespace std;

template <class T> int extractMin(vector<int>& q, T* distances)
{
	int ind = 0;
	int min = q[0];
	for (int i = 1; i < q.size(); i++)
	{
		if (distances[q[i]] < distances[min])
		{
			min = q[i];
			ind = i;
		}
	}
	q[ind] = q[q.size() - 1];
	q.pop_back();
	return min;
}

template <class H, class T> int Dijkstra(Graph<H, T>* graph, H keysrc, T*& distances, int*& predecessors)
{
	int src = graph->findIndex(keysrc);
	if (src == -1)
		return 0;
	int V = graph->getCurrentNodeNumber();
	distances = new T[V];
	predecessors = new int[V];	
	vector<int> q= vector<int>(V);	
	for (int i = 0; i < V; i++)
	{
		distances[i] = INT_MAX;
		predecessors[i] = -1;
		q[i] = i;
	}
	distances[src] = 0;
	predecessors[src] = src;
	
	while (!q.empty())
	{
		int tmp = extractMin(q, distances);		
		if (distances[tmp] == INT_MAX)
			break;
		for (int i = 0; i < V; i++) //looking for neighboors
		{
			if (graph->getGraphIndexMatrix()[tmp][i] == 1)
			{
				T newval = distances[tmp] + graph->getWeightMatrix()[tmp][i];
				if (newval < distances[i])
				{
					distances[i] = newval;
					predecessors[i] = tmp;					
				}
			}
		}
	}
	return 1;
}

template <class H, class T> void printDistances(Graph<H, T>* graph, H key, T* distances, int* predecessors)
{
	cout << "Printing Dijkstra distances" << endl;
	if (predecessors == NULL || graph->findIndex(key) < 0)
		return;	
	int src = graph->findIndex(key);
	int V = graph->getCurrentNodeNumber();
	for (int i = 0; i < V; i++)
		cout << "Distance from " << key << " to " << *(graph->getKey(i)) << " is " << distances[i] << endl;
	cout << "Printing predecessor list" << endl;
	for (int i = 0; i < V; i++)
	{
		if (predecessors[i] > -1 )
			cout << "The predecessor of " << *(graph->getKey(i)) << " is " << *(graph->getKey(predecessors[i])) << endl;
		else
			cout<< *(graph->getKey(i)) << " is unreacheable" << endl;		
	}
	return;
}


int main()
{
	Graph<char, int>* g = new Graph<char, int>(5);
	g->addNode('A')->addRootNode('C')->addRootNode('B')->addNode('D')->addNode('E');
	g->addEdge('C', 'B', 4)->addEdge('C', 'A', 19)->addEdge('B', 'A', 1)->addEdge('B', 'D', 2)->addEdge('A', 'D', 9)->addEdge('D', 'E', 3)->addEdge('B', 'E', 8)->addEdge('E', 'C', 1);
	g->print();
	int* distances = NULL;
	int* predecessors = NULL;
	if (Dijkstra(g, 'B', distances, predecessors))
		printDistances(g, 'B', distances, predecessors);
	return 1;
}