#include<iostream>
#include<list>
#include<vector>
using namespace std;

class MatrixGraph {
private:
	class Vertex;
	class Edge;
	Vertex* find_vertex(int vid);
	Edge* find_edge(int eid);

	bool is_adjacent_to(Vertex* v,Vertex* u);
	list<Edge*> incident_edges(Vertex* v);
	bool erase_edge(Edge* e);

	list<Vertex*> vertices_list;
	list<Edge*> edges_list;
	vector<vector<Edge*>> matrix;
	
public:
	MatrixGraph() = default;

	
};
