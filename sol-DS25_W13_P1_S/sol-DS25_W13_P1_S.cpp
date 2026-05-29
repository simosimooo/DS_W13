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
		Vertex(int vid, int matrixIdx):vid(vid),matrixIdx(matrixIdx){}
	};
	class Edge {
	private:
		Vertex* src;
		Vertex* dst;
		int weight;
		list<Edge*>::iterator edgesPos;
		friend class MatrixGraph;
	public:
		Edge(Vertex* src,Vertex* dst,int weight):src(src),dst(dst),weight(weight){}
	};
	
	list<Vertex*> vertices;
	list<Edge*> edges;
	vector<vector<Edge*>> matrix;
	Vertex* findVertex(int vid) {
		for (Vertex* v : vertices)if (v->vid == vid)return v;
		return nullptr;
	}
	Edge* findEdge(Vertex* u, Vertex* v) {
		return matrix[u->matrixIdx][v->matrixIdx];
	}
	void eraseEdge(Edge* e) {
		if (e == nullptr)return;
		int srcIdx = e->src->matrixIdx;
		int dstIdx = e->dst->matrixIdx;
		edges.erase(e->edgesPos);
		matrix[srcIdx][dstIdx] = matrix[dstIdx][srcIdx] = nullptr;
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
	int degree(Vertex* v) {
		return incidentEdges(v).size();
	}
public:
	MatrixGraph() = default;

	void insertVertex(int vid) {
		if (findVertex(vid) != nullptr) { cout << "Vertex Exist\n"; return; }
		Vertex* newVertex = new Vertex(vid, matrix.size());
		vertices.push_back(newVertex);
		newVertex->verticesPos = --vertices.end();
		for (vector<Edge*>& arr : matrix) {
			arr.push_back(nullptr);
		}
		matrix.emplace_back(matrix.size() + 1, nullptr);
	}
	void insertEdge(int vid1, int vid2, int weight) {
		Vertex* src = findVertex(vid1);
		Vertex* dst = findVertex(vid2);
		if (src == nullptr && dst == nullptr) { cout << vid1 << ' ' << vid2 << " Vertex Not Exist\n"; return; }
		if (src == nullptr || dst == nullptr) { cout << (src == nullptr ? vid1 : vid2) << " Vertex Not Exist\n"; return; }
		if (findEdge(src, dst) != nullptr) { cout << "Edge Exist\n"; return; }
		Edge* newEdge = new Edge(src, dst, weight);
		edges.push_back(newEdge);
		newEdge->edgesPos = --edges.end();
		matrix[src->matrixIdx][dst->matrixIdx] = matrix[dst->matrixIdx][src->matrixIdx] = newEdge;
	}
	void eraseVertex(int vid) {
		Vertex* v = findVertex(vid);
		if (v == nullptr) { cout << vid << " Vertex Not Exist\n"; return; }
		list<Edge*> incidentList = incidentEdges(v);
		for (Edge* e : incidentList)eraseEdge(e);
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
	void updateEdge(int vid1, int vid2, int weight) {
		Vertex* src = findVertex(vid1);
		Vertex* dst = findVertex(vid2);
		if (src == nullptr && dst == nullptr) { cout << vid1 << ' ' << vid2 << " Vertex Not Exist\n"; return; }
		if (src == nullptr || dst == nullptr) { cout << (src == nullptr ? vid1 : vid2) << " Vertex Not Exist\n"; return; }
		if (findEdge(src,dst) == nullptr) { cout << -1 << '\n'; return; }
		Edge* e = findEdge(src, dst);
		e->weight = weight;
	}
	void sumEdgeWeight(int vid) {
		Vertex* v = findVertex(vid);
		if (v == nullptr) { cout << vid << " Vertex Not Exist\n"; return; }
		list<Edge*> incidentList = incidentEdges(v);
		int sum = 0;
		for (Edge* e : incidentList)sum += e->weight;
		cout << sum << '\n';
	}
	void maxDegree() {
		if (vertices.empty()) { cout << -1 << '\n'; return; }
		int cnt = 1;
		Vertex* maxVer = vertices.front();
		for (Vertex* v : vertices) {
			if (v == vertices.front())continue;
			if (degree(maxVer) == degree(v)) {
				++cnt;
				if (maxVer->vid < v->vid)maxVer = v;
			}
			if (degree(maxVer) < degree(v)) {
				cnt = 1;
				maxVer = v;
			}
		}
		cout << maxVer->vid << ' ' << degree(maxVer) << ' ' << cnt<<'\n';
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
		else if (cmd == "maxDegree") {
			graph.maxDegree();
		}
	}
}