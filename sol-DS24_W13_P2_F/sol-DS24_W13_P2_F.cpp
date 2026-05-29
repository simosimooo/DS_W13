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
	list<Edge*>Edges;
	vector<vector<Edge*>>matrix;
	Vertex* findVertex(int vid) {
		for (Vertex* v : vertices)if (v->vid == vid)return v;
		return nullptr;
	}
	Edge* findEdge(Vertex* u, Vertex* v) {
		return matrix[u->matrixIdx][v->matrixIdx];
	}
	list<Vertex*>adjacentVertices(Vertex* v) {
		list<Vertex*>res;
		
	}
};