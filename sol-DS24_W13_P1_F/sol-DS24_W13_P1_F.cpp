#include<iostream>
#include<string>
#include<vector>
#include<list>
using namespace std;

class MatrixGraph {
private:
	class Vertex {
	private:
		int vid;
		int matrixIdx;
		list<Vertex*>::iterator verticesPos;
		friend class MatrixGraph;
	public:
		Vertex(int vid,int matrixIdx):vid(vid),matrixIdx(matrixIdx){}
	};
	class Edge {
	private:
		Vertex* src;
		Vertex* dst;
		list<Edge*>::iterator edgesPos;
		friend class MatrixGraph;
	public:
		Edge(Vertex* src, Vertex* dst) :src(src), dst(dst){}
	};
	list<Vertex*>vertices;
	list<Edge*>edges;
	vector<vector<Edge*>>matrix;

	Vertex* findVertex(int vid) {
		for (Vertex* v : vertices)if (v->vid == vid)return v;
		return nullptr;
	}
	Edge* findEdge(Vertex* src, Vertex* dst) {
		return matrix[src->matrixIdx][dst->matrixIdx];
	}
	void eraseEdge(Edge* e) {
		if (e == nullptr) { cout << "None\n"; return; }
		int srcIdx = e->src->matrixIdx;
		int dstIdx = e->dst->matrixIdx;
		matrix[srcIdx][dstIdx] = matrix[dstIdx][srcIdx] = nullptr;
		edges.erase(e->edgesPos);
		delete e;
	}
	list<Edge*> incidentEdges(Vertex* v) {
		list<Edge*> res;
		int matrixIdx = v->matrixIdx;
		for (int i{ 0 }; i < matrix.size(); ++i) {
			if (i == matrixIdx)continue;
			if (matrix[i][matrixIdx] != nullptr)res.push_back(matrix[i][matrixIdx]);
		}
		return res;
	}
public:
	MatrixGraph() = default;

	void insertVertex(int vid) {
		if (findVertex(vid) != nullptr) { cout << "Exist\n"; return; }
		Vertex* newVertex = new Vertex(vid, matrix.size());
		vertices.push_back(newVertex);
		newVertex->verticesPos = --vertices.end();
		for (vector<Edge*>& arr : matrix) {
			arr.push_back(nullptr);
		}
		matrix.emplace_back(matrix.size() + 1, nullptr);
	}
	void insertEdge(int vid1, int vid2) {
		Vertex* src = findVertex(vid1);
		Vertex* dst = findVertex(vid2);
		if (findEdge(src, dst) != nullptr) { cout << "Exist\n"; return; }
		Edge* newEdge = new Edge(src, dst);
		edges.push_back(newEdge);
		newEdge->edgesPos = --edges.end();
		matrix[src->matrixIdx][dst->matrixIdx] = matrix[dst->matrixIdx][src->matrixIdx] = newEdge;
	}
	void eraseVertex(int vid) {
		Vertex* v = findVertex(vid);
		list<Edge*> incidentList = incidentEdges(v);
		for (Edge* e : incidentList) {
			eraseEdge(e);
		}
		int matrixIdx = v->matrixIdx;
		for (int i{ 0 }; i < matrix.size(); ++i) {
			if (i == matrixIdx)continue;
			matrix[i].erase(matrix[i].begin() + matrixIdx);
		}
		matrix.erase(matrix.begin() + matrixIdx);
		for (Vertex* other : vertices) {
			if (other->matrixIdx > matrixIdx)--other->matrixIdx;
		}
		vertices.erase(v->verticesPos);
		delete v;
	}
	void eraseEdge(int vid1, int vid2) {
		eraseEdge(findEdge(findVertex(vid1),findVertex(vid2)));
	}
	void isAdjacent(int vid1, int vid2) {
		Vertex* u = findVertex(vid1);
		Vertex* v = findVertex(vid2);
		int deg1 = incidentEdges(u).size();
		int deg2 = incidentEdges(v).size();
		bool adjacent = false;
		if (matrix[u->matrixIdx][v->matrixIdx] != nullptr || matrix[v->matrixIdx][u->matrixIdx] != nullptr) {
			adjacent = true;
		}
		cout << (adjacent ? "True" : "False") << ' ';
		if (deg1 > deg2)cout << vid2;
		else if (deg1 < deg2)cout << vid1;
		else cout << (u->vid > v->vid ? vid2 : vid1);
		cout << '\n';
	}
	void minVertexInfo() {
		if (vertices.empty()) { cout << -1 << '\n'; return; }
		Vertex* minVertex = vertices.front();
		for (Vertex* v : vertices) {
			if (v == vertices.front())continue;
			if (minVertex->vid > v->vid)minVertex = v;
		}
		cout << minVertex->vid << ' ' << incidentEdges(minVertex).size() << '\n';
	}
};

int main() {
	int T;
	cin >> T;
	MatrixGraph graph;
	while (T--) {
		string cmd;
		cin >> cmd;
		if (cmd == "insertVertex") {
			int S;
			cin >> S;
			graph.insertVertex(S);
		}
		else if (cmd == "insertEdge") {
			int S, D;
			cin >> S >> D;
			graph.insertEdge(S, D);
		}
		else if (cmd == "eraseVertex") {
			int S;
			cin >> S;
			graph.eraseVertex(S);
		}
		else if (cmd == "eraseEdge") {
			int S, D;
			cin >> S >> D;
			graph.eraseEdge(S, D);
		}
		else if (cmd == "isAdjacent") {
			int S, D;
			cin >> S >> D;
			graph.isAdjacent(S, D);
		}
		else if (cmd == "minVertexInfo") {
			graph.minVertexInfo();
		}
	}
}