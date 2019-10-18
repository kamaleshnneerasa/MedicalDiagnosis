#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Graph_Node.h"

// The whole network represted as a list of nodes
class Network{

	list <Graph_Node> Pres_Graph;

public:
	int addNode(Graph_Node node);
	int netSize();
    // get the index of node with a given name
    int get_index(string val_name);
// get the node at nth index
    list<Graph_Node>::iterator get_nth_node(int n);
    //get the iterator of a node with a given name
    list<Graph_Node>::iterator search_node(string val_name);
    static Network read_network();
};
