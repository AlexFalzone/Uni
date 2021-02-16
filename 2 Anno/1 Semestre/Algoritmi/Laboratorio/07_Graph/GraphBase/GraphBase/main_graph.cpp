#include "graph.cpp"

int main()
{
	int def = 0;
	Graph<char, int>* g = new Graph<char, int>(4);
	g->addNode('A')->addRootNode('C')->addRootNode('B')->addNode('D');
	g->addEdge('C', 'B', def)->addEdge('C', 'A', def)->addEdge('C', 'C', def)->addEdge('B', 'D', def)->addEdge('A', 'D', def);
	cout << "Max size of the graph: " << g->getMaxNodeNumber() << endl;
	cout << "Current node number: " << g->getCurrentNodeNumber() << endl;
	cout << "Current edge number: " << g->getCurrentEdgeNumber() << endl;
	g->print();
	cout << "The root is " << *(g->getRootNode()) << " at index " << g->getRootIndex() << endl;
	cout << "We now change the root" << endl;
	g->setRootNode('C');
	cout << "The new root is " << *(g->getRootNode()) << " at index " << g->getRootIndex() << endl;
	cout << "We now delete some edges" << endl;
	g->deleteEdge('C', 'A')->deleteEdge('B', 'D');
	cout << "Current edge number: " << g->getCurrentEdgeNumber() << endl;
	g->print();
	cout << "Modifying graph" << endl;
	g->addEdge('C', 'A', def)->addEdge('B', 'D', def)->addEdge('A', 'C', def)->addEdge('B', 'C', def);
	g->print();
	cout << "Deleting node" << endl;
	//change the root node before deleting
	g->setRootNode('B');
	g->deleteNode('C');
	g->print();
	return 0;
}