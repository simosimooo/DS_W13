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

	list<Vertex*> vertices_list;
	list<Edge*> edges_list;
	vector<vector<Edge*>> matrix;

	bool is_adjacent_to(Vertex* u, Vertex* v);
	list<Edge*> incident_edges(Vertex* v);
	bool erase_edge(Edge* e);

public:
	MatrixGraph() = default;

	list<int> vertices();
	list<int> edges();

	bool is_adjacent_to(int vid1, int vid2);
	list<int> incident_edges(int vid);
	bool insert_vertex(int vid);
	bool insert_edge(int vid1, int vid2, int eid);
	bool erase_vertex(int vid);
	bool erase_edge(int eid);
};

class MatrixGraph::Vertex {
private:
	int vid;
	int matrix_idx;
	list<Vertex*>::iterator vertices_list_pos;
	friend class MatrixGraph;
public:
	Vertex(int vid,int matrix_idx):vid(vid),matrix_idx(matrix_idx){}
};

class MatrixGraph::Edge {
private:
	int eid;
	Vertex* src;
	Vertex* dst;
	list<Edge*>::iterator edges_list_pos;
	friend class MatrixGraph;
public:
	Edge(int eid,Vertex* src,Vertex* dst):eid(eid),src(src),dst(dst){}
};

list<int> MatrixGraph::vertices() {
	list<int> res;
	for (Vertex* v : vertices_list)res.push_back(v->vid);
	return res;
}

list<int> MatrixGraph::edges() {
	list<int> res;
	for (Edge* e : edges_list)res.push_back(e->eid);
	return res;
}

MatrixGraph::Vertex* MatrixGraph::find_vertex(int vid) {
	for (Vertex* v : vertices_list)if (v->vid == vid)return v;
	return nullptr;
}

MatrixGraph::Edge* MatrixGraph::find_edge(int eid) {
	for (Edge* e : edges_list)if (e->eid == eid)return e;
	return nullptr;
}

bool MatrixGraph::is_adjacent_to(int vid1, int vid2) {
	return is_adjacent_to(find_vertex(vid1), find_vertex(vid2));
}
bool MatrixGraph::is_adjacent_to(Vertex* u, Vertex* v) {
	if (u == nullptr || v == nullptr)return false;
	return matrix[u->matrix_idx][v->matrix_idx] != nullptr || matrix[v->matrix_idx][u->matrix_idx] != nullptr;
}

list<int> MatrixGraph::incident_edges(int vid) {
	list<Edge*> incident_edges_list = incident_edges(find_vertex(vid));
	list<int>res;
	for (Edge* e : incident_edges_list)res.push_back(e->eid);
	return res;
}
list<MatrixGraph::Edge*> MatrixGraph::incident_edges(Vertex* v) {
	if (v == nullptr)return {};
	list<Edge*> res;
	int matrix_idx = v->matrix_idx;
	for (int i{ 0 }; i < matrix.size(); ++i) {
		if (i == matrix_idx)continue;
		if (matrix[i][matrix_idx] != nullptr)res.push_back(matrix[i][matrix_idx]);
	}
	return res;
}

bool MatrixGraph::insert_vertex(int vid) {
	if (find_vertex(vid) != nullptr)return false;
	Vertex* newVertex = new Vertex(vid, matrix.size());
	vertices_list.push_back(newVertex);
	newVertex->vertices_list_pos = --vertices_list.end();

	for (vector<Edge*>& arr : matrix)arr.push_back(nullptr);
	matrix.emplace_back(matrix.size() + 1, nullptr);
	return true;
}

bool MatrixGraph::insert_edge(int vid1, int vid2, int eid) {
	Vertex* src = find_vertex(vid1);
	Vertex* dst = find_vertex(vid2);
	if (src == nullptr || dst == nullptr)return false;
	if (find_edge(eid) != nullptr)return false;
	if (is_adjacent_to(src, dst))return false;

	Edge* newEdge = new Edge(eid, src, dst);
	edges_list.push_back(newEdge);
	newEdge->edges_list_pos = --edges_list.end();

	matrix[src->matrix_idx][dst->matrix_idx] = matrix[dst->matrix_idx][src->matrix_idx] = newEdge;
	return true;
}

bool MatrixGraph::erase_vertex(int vid) {
	Vertex* v = find_vertex(vid);
	if (v == nullptr)return false;
	
	for (Edge* e : incident_edges(v))erase_edge(e);
	
	int matrix_idx = v->matrix_idx;
	for (int i{ 0 }; i < matrix.size(); ++i) {
		if (i == matrix_idx)continue;

		matrix[i].erase(matrix[i].begin() + matrix_idx);
	}
	matrix.erase(matrix.begin() + matrix_idx);

	for (Vertex* other : vertices_list) {
		if (other->matrix_idx > matrix_idx)--other->matrix_idx;
	}
	vertices_list.erase(v->vertices_list_pos);
	delete v;
	return true;
}

bool MatrixGraph::erase_edge(int eid) {
	return erase_edge(find_edge(eid));
}
bool MatrixGraph::erase_edge(Edge* e) {
	if (e == nullptr)return false;

	int src_idx = e->src->matrix_idx;
	int dst_idx = e->dst->matrix_idx;
	matrix[src_idx][dst_idx] = matrix[dst_idx][src_idx] = nullptr;

	edges_list.erase(e->edges_list_pos);
	delete e;
	return true;
}