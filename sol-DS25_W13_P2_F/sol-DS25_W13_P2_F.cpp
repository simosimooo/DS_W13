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
		list<Vertex*>::iterator verticesListPos;
		friend class MatrixGraph;
	public:
		Vertex(int vid, int matrixIdx) :vid(vid), matrixIdx(matrixIdx){}
	};
	
	class Edge {
	private:
		int eid;
		Vertex* src;
		Vertex* dst;
		list<Edge*>::iterator edgesListPos;
		friend class MatrixGraph;
	public:
		Edge(int eid,Vertex* src,Vertex* dst):eid(eid),src(src),dst(dst){}
	};

	list<Vertex*> verticesList;
	list<Edge*> edgesList;
	vector<vector<Edge*>> matrix;

	Vertex* findVertex(int vid) {
		for (Vertex* v : verticesList)if (v->vid == vid)return v;
		return nullptr;
	}
	Edge* findEdge(int eid) {
		for (Edge* e : edgesList)if (e->eid == eid)return e;
		return nullptr;
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

};

int main() {
	int N;
	cin >> N;

}