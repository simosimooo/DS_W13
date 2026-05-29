#include<iostream>
#include<string>
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
	Edge* find_edge(Vertex* u,Vertex* v) {
		return matrix[u->matrix_idx][v->matrix_idx];
	}

	bool is_adjacent_to(Vertex* u, Vertex* v) {
		if (u == nullptr || v == nullptr)return false;
		return matrix[u->matrix_idx][v->matrix_idx] != nullptr || matrix[v->matrix_idx][u->matrix_idx];
	}
	bool is_adjacent_to(int vid1, int vid2) {
		return is_adjacent_to(find_vertex(vid1), find_vertex(vid2));
	}
	list<Edge*> incident_edges(Vertex* v) {
		if (v == nullptr)return{};
		list<Edge*> res;
		int matrix_idx = v->matrix_idx;
		for (int i{ 0 }; i < matrix.size(); ++i) {
			if (i == matrix_idx)continue;
			if (matrix[i][matrix_idx] != nullptr)res.push_back(matrix[i][matrix_idx]);
		}
		return res;
	}
	void erase_edge(Edge* e) {
		if (e == nullptr)return;
		int src_idx = e->src->matrix_idx;
		int dst_idx = e->dst->matrix_idx;
		matrix[src_idx][dst_idx] = matrix[dst_idx][src_idx] = nullptr;
		edges_list.erase(e->edges_list_pos);
		delete e;
	}
public:

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
		if (src == nullptr && dst == nullptr) { cout << vid1 << ' ' << vid2 << " Vertex Not Exist\n"; return; }
		if (src == nullptr || dst == nullptr) { cout << (src == nullptr ? vid1 : vid2) << " Vertex Not Exist\n"; return; }
		if(is_adjacent_to(vid1,vid2)){cout<<"Edge Exist\n";return; }
		Edge* newEdge = new Edge(eid, src, dst);
		edges_list.push_back(newEdge);
		newEdge->edges_list_pos = --edges_list.end();
		matrix[src->matrix_idx][dst->matrix_idx] = matrix[dst->matrix_idx][src->matrix_idx] = newEdge;
	}

	void eraseVertex(int vid) {
		if (find_vertex(vid) == nullptr) { cout << vid << " Vertex Not Exist\n"; return; }
		Vertex* v = find_vertex(vid);
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
	}

	void updateEdge(int vid1, int vid2, int eid) {
		Vertex* src = find_vertex(vid1);
		Vertex* dst = find_vertex(vid2);
		if (src == nullptr && dst == nullptr) { cout << vid1 << ' ' << vid2 << " Vertex Not Exist\n"; return; }
		if (src == nullptr || dst == nullptr) {	cout << (src == nullptr ? vid1 : vid2) << " Vertex Not Exist\n"; return; }
		if (!is_adjacent_to(vid1, vid2)) { cout << -1 << '\n'; return; }
		find_edge(src, dst)->eid = eid;
	}
	void sumEdgeWeight(int vid) {
		Vertex* v = find_vertex(vid);
		if (v == nullptr) { cout << vid << " Vertex Not Exist\n"; return; }
		int sum = 0;
		list<Edge*> incident_edges_list = incident_edges(v);
		for (Edge* e : incident_edges_list)sum += e->eid;
		cout << sum << '\n';
	}
	void minDegree() {
		if (vertices_list.empty()) { cout << -1 << '\n'; return; }
		int minNum = 1;
		Vertex* minVertex = vertices_list.front();
		for (Vertex* v : vertices_list) {
			if (v == vertices_list.front())continue;
			int minDeg = incident_edges(minVertex).size();
			int vDeg = incident_edges(v).size();
			if (minDeg > vDeg) {
				minVertex = v;
				minNum = 1;
			}
			else if (minDeg == vDeg) {
				++minNum;
				if (minVertex->vid > v->vid)minVertex = v;
			}
		}
		cout << minVertex->vid << ' ' << incident_edges(minVertex).size() << ' ' << minNum << '\n';
	}
};

int main() {
	int N;
	cin >> N;
	MatrixGraph graph;
	while (N--) {
		string cmd;
		cin >> cmd;
		if (cmd == "insertVertex") {
			int s;
			cin >> s;
			graph.insertVertex(s);
		}
		else if (cmd == "insertEdge") {
			int s, d, w;
			cin >> s >> d >> w;
			graph.insertEdge(s, d, w);
		}
		else if (cmd == "eraseVertex") {
			int s;
			cin >> s;
			graph.eraseVertex(s);
		}
		else if (cmd == "updateEdge") {
			int s, d, w;
			cin >> s >> d >> w;
			graph.updateEdge(s, d, w);
		}
		else if (cmd == "sumEdgeWeight") {
			int s;
			cin >> s;
			graph.sumEdgeWeight(s);
		}
		else if (cmd == "minDegree") {
			graph.minDegree();
		}
	}
}