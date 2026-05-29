#include<iostream>
#include<string>
#include<list>
#include<vector>
#include<algorithm>
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
		int eid;
		Vertex* src;
		Vertex* dst;
		list<Edge*>::iterator edgesPos;
		friend class MatrixGraph;
	public:
		Edge(int eid,Vertex* src,Vertex* dst):eid(eid),src(src),dst(dst){}
	};
	list<Vertex*>vertices;
	list<Edge*>edges;
	vector<vector<Edge*>>matrix;
	Vertex* findVertex(int vid) {
		for (Vertex* v : vertices)if (v->vid == vid)return v;
		return nullptr;
	}
	Edge* findEdge(int eid) {
		for (Edge* e : edges)if (e->eid == eid)return e;
		return nullptr;
	}
	bool isAdjacent(Vertex* u, Vertex* v) {
		if (u == nullptr || v == nullptr)return false;
		return matrix[u->matrixIdx][v->matrixIdx] != nullptr || matrix[v->matrixIdx][u->matrixIdx] != nullptr;
	}
	list<Edge*>incidentEdges(Vertex* v) {
		if (v == nullptr)return{};
		list<Edge*>res;
		int matrixIdx = v->matrixIdx;
		for (int i{ 0 }; i < matrix.size(); ++i) {
			if (i == matrixIdx)continue;
			if (matrix[i][matrixIdx] != nullptr)res.push_back(matrix[i][matrixIdx]);
		}
		return res;
	}
	void eraseEdge(Edge* e) {
		if (e == nullptr)return;
		edges.erase(e->edgesPos);
		int srcIdx = e->src->matrixIdx;
		int dstIdx = e->dst->matrixIdx;
		matrix[srcIdx][dstIdx] = matrix[dstIdx][srcIdx] = nullptr;
		delete e;
	}
	vector<Vertex*>adjacentVertices(Vertex* v) {
		if (v == nullptr)return{};
		vector<Vertex*>res;
		for (Vertex* ver : vertices) {
			if (isAdjacent(ver, v)&&ver!=v)res.push_back(ver);
		}
		return res;
	}
public:
	MatrixGraph() = default;

	void signup(int vid) {
		if (findVertex(vid) != nullptr)return;
		Vertex* newVertex = new Vertex(vid, matrix.size());
		vertices.push_back(newVertex);
		newVertex->verticesPos = --vertices.end();
		for (vector<Edge*>& arr : matrix)arr.push_back(nullptr);
		matrix.emplace_back(matrix.size() + 1, nullptr);
	}
	void make_friend(int vid1, int vid2, int eid) {
		Vertex* src = findVertex(vid1);
		Vertex* dst = findVertex(vid2);
		if (src == nullptr || dst == nullptr) { cout << "error\n"; return; }
		if (findEdge(eid) != nullptr) { cout << "error\n"; return; }
		if (isAdjacent(src, dst)) { cout << "error\n"; return; }
		Edge* newEdge = new Edge(eid, src, dst);
		edges.push_back(newEdge);
		newEdge->edgesPos = --edges.end();
		matrix[src->matrixIdx][dst->matrixIdx] = matrix[dst->matrixIdx][src->matrixIdx] = newEdge;
	}
	void leave(int vid) {
		Vertex* v = findVertex(vid);
		if (v == nullptr)return;
		list<Edge*>incidents = incidentEdges(v);
		for (Edge* e : incidents) {
			eraseEdge(e);
		}
		int matrixIdx = v->matrixIdx;
		for (int i{ 0 }; i < matrix.size(); ++i) {
			matrix[i].erase(matrix[i].begin() + matrixIdx);
		}
		matrix.erase(matrix.begin() + matrixIdx);
		for (Vertex* other : vertices) {
			if (other->matrixIdx > matrixIdx)--other->matrixIdx;
		}
		vertices.erase(v->verticesPos);
		delete v;
	}
	void break_friend(int eid) {
		eraseEdge(findEdge(eid));
	}
	void popularity(int vid) {
		Vertex* v = findVertex(vid);
		if (v == nullptr) { cout << "error\n"; return; }
		cout << incidentEdges(v).size() << '\n';
	}
	void recommend_friend(int vid) {
		Vertex* v = findVertex(vid);
		if (v == nullptr) { cout << -1 << '\n'; return; }
		vector<Vertex*>friendFriends;
		vector<Vertex*>friends = adjacentVertices(v);
		for (Vertex* ver : friends) {
			vector<Vertex*>ff = adjacentVertices(ver);
			for (Vertex* vert : ff) {
				bool push = true;
				if (!isAdjacent(vert, v) && vert != v) {
					for (Vertex* vertex : friendFriends) {
						if (vertex == vert)push = false;
					}
				}
				if (push)friendFriends.push_back(vert);
			}
		}
		if (friendFriends.empty()) { cout << -1 << '\n'; return; }
		vector<int>rec;
		for (Vertex* ver : friendFriends) {
			rec.push_back(ver->vid);
		}
		sort(rec.begin(), rec.end());
		for (int e : rec) {
			cout << e << ' ';
		}
		cout << '\n';
	}
};

int main() {
	int Q;
	cin >> Q;
	MatrixGraph graph;
	while (Q--) {
		string cmd;
		cin >> cmd;
		if (cmd == "signup") {
			int n;
			cin >> n;
			graph.signup(n);
		}
		else if (cmd == "make_friend") {
			int u, v, e;
			cin >> u >> v >> e;
			graph.make_friend(u, v, e);
		}
		else if (cmd == "leave") {
			int n;
			cin >> n;
			graph.leave(n);
		}
		else if (cmd == "break_friend") {
			int e;
			cin >> e;
			graph.break_friend(e);
		}
		else if (cmd == "popularity") {
			int n;
			cin >> n;
			graph.popularity(n);
		}
		else if (cmd == "recommend_friend") {
			int u;
			cin >> u;
			graph.recommend_friend(u);
		}
	}
}