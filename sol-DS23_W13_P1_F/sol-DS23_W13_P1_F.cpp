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
		Edge(Vertex* src,Vertex* dst):src(src),dst(dst){}
	};
	list<Vertex*>vertices;
	list<Edge*>edges;
	vector<vector<Edge*>>matrix;
	
	Vertex* findVertex(int vid) {
		for (Vertex* v : vertices)if (v->vid == vid)return v;
		return nullptr;
	}
	Edge* findEdge(Vertex* u, Vertex* v) {
		return matrix[u->matrixIdx][v->matrixIdx];
	}
	list<Edge*> incidentEdges(Vertex* v) {
		list<Edge*>res;
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
	void eraseEdge(int vid1, int vid2) {
		Vertex* src = findVertex(vid1);
		Vertex* dst = findVertex(vid2);
		if (findEdge(src, dst) == nullptr) { cout << "None\n"; return; }
		Edge* e = findEdge(src, dst);
		edges.erase(e->edgesPos);
		matrix[src->matrixIdx][dst->matrixIdx] = matrix[dst->matrixIdx][src->matrixIdx] = nullptr;
		delete e;
	}
	void isAdjacentOdd(int vid) {
		list<Edge*>incidentList = incidentEdges(findVertex(vid));
		int adjacentNum = incidentList.size();
		cout << (adjacentNum % 2 == 1 ? "True " : "False ") << adjacentNum << '\n';
	}
	void minEdgeVertex() {
		if (vertices.empty()) { cout << -1 << '\n'; return; }
		Vertex* minVer = vertices.front();
		for (Vertex* v : vertices) {
			if (v == vertices.front())continue;
			if (incidentEdges(minVer).size() > incidentEdges(v).size())minVer = v;
			else if (incidentEdges(minVer).size() == incidentEdges(v).size() && minVer->vid > v->vid)minVer = v;
		}
		if (incidentEdges(minVer).empty()) { cout << -1 << '\n'; return; }
		cout << minVer->vid << '\n';
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
		else if (cmd == "eraseEdge") {
			int S, D;
			cin >> S >> D;
			graph.eraseEdge(S, D);
		}
		else if (cmd == "isAdjacentOdd") {
			int S;
			cin >> S;
			graph.isAdjacentOdd(S);
		}
		else if (cmd == "minEdgeVertex") {
			graph.minEdgeVertex();
		}
	}
}