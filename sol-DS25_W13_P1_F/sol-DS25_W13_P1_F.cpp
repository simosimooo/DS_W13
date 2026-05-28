#include<iostream>
#include<list>
#include<vector>
using namespace std;

class MatrixGraph {
private:
	class Vertex {
	private:
		int vid;
		int matrix_idx;
		list<Vertex*>::iterator vertices_list_pos;
		friend class MatrixGraph;
	public:
		Vertex(int vid,int matrix_idx):vid(vid),matrix_idx(matrix_idx){}
	};
	class Edge {
	private:
		int eid;
		Vertex* src;
		Vertex* dst;
		list<Edge*>::iterator edges_list_pos;
		friend class MatrixGraph;
	public:
		Edge(int eid,Vertex* src,Vertex* dst):eid(eid),src(src),dst(dst){}
	};

	list<Vertex*> vertices_list;
	list<Edge*> edges_list;
	vector<vector<Edge*>> matrix;

	Vertex* find_vertex(int vid) {
		for (Vertex* v : vertices_list)if (v->vid == vid)return v;
		return nullptr;
	}
	Edge* find_edge(int eid) {
		for (Edge* e : edges_list)if (e->eid == eid)return e;
		return nullptr;
	}
	
	void insertVertex(int vid) {
		if (find_vertex(vid) != nullptr) { cout << "Vertex Exist\n"; return; }

		Vertex* newVertex = new Vertex(vid, matrix.size());
		vertices_list.push_back(newVertex);
		newVertex->vertices_list_pos = --vertices_list.end();

		for (vector<Edge*>& arr : matrix)arr.push_back(nullptr);
		matrix.emplace_back(matrix.size() + 1, nullptr);
	}
	void insertEdge(int vid1, int vid2, int eid) {
		Vertex* src = find_vertex(vid1);
		Vertex* dst = find_vertex(vid2);
		if (src == nullptr || dst == nullptr)return;
	}
};