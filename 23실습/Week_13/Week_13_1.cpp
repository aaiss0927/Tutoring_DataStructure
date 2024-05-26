#include <iostream>
#include <vector>
using namespace std;

struct Vertex {
	int vertexId;
	int matrixId;
	Vertex* prev;
	Vertex* next;

	Vertex() {
		vertexId = matrixId = -1;
		prev = next = nullptr;
	}

	Vertex(int vertexId) {
		this->vertexId = vertexId;
		matrixId = -1;
		prev = next = nullptr;
	}
};

struct Edge {
	Vertex* src;
	Vertex* dst;
	Edge* prev;
	Edge* next;

	Edge() {
		src = dst = nullptr;
		prev = next = nullptr;
	}

	Edge(Vertex* src, Vertex* dst) {
		this->src = src;
		this->dst = dst;
		prev = next = nullptr;
	}
};

class VertexList {
private:
	Vertex* header;
	Vertex* trailer;

public:
	VertexList() {
		header = new Vertex();
		trailer = new Vertex();
		header->next = trailer;
		trailer->prev = header;
		header->matrixId = -1;
	}

	void insertVertex(Vertex* newVertex) {    // push_back()
		newVertex->prev = trailer->prev;
		newVertex->next = trailer;
		trailer->prev->next = newVertex;
		trailer->prev = newVertex;
		newVertex->matrixId = newVertex->prev->matrixId + 1;    // modified
	}

	void eraseVertex(Vertex* delVertex) {
		for (Vertex* cur = delVertex->next; cur != trailer; cur = cur->next) {
			cur->matrixId--;
		}

		delVertex->prev->next = delVertex->next;
		delVertex->next->prev = delVertex->prev;
		delete delVertex;
	}

	Vertex* findVertex(int vertexId) {
		for (Vertex* cur = header->next; cur != trailer; cur = cur->next) {
			if (cur->vertexId == vertexId)
				return cur;
		}

		return nullptr;
	}

	Vertex* findVertex_by_matrixId(int matrixId) {
		for (Vertex* cur = header->next; cur != trailer; cur = cur->next) {
			if (cur->matrixId == matrixId)
				return cur;
		}

		return nullptr;
	}
};

class EdgeList {
private:
	Edge* header;
	Edge* trailer;

public:
	EdgeList() {
		header = new Edge();
		trailer = new Edge();
		header->next = trailer;
		trailer->prev = header;
	}

	void insertEdge(Edge* newEdge) {    // push_back()
		newEdge->prev = trailer->prev;
		newEdge->next = trailer;
		trailer->prev->next = newEdge;
		trailer->prev = newEdge;
	}

	void eraseEdge(Edge* delEdge) {
		delEdge->prev->next = delEdge->next;
		delEdge->next->prev = delEdge->prev;
		delete delEdge;
	}
};

class Graph {
private:
	vector<vector<Edge*>> EdgeMatrix;
	VertexList vList;
	EdgeList eList;

public:
	void insertVertex(int vertexId) {
		if (vList.findVertex(vertexId) != nullptr) {
			cout << "Exist\n";
			return;
		}

		Vertex* newVertex = new Vertex(vertexId);

		for (int i = 0; i < EdgeMatrix.size(); i++) {
			EdgeMatrix[i].push_back(nullptr);
		}
		EdgeMatrix.push_back(vector<Edge*>(EdgeMatrix.size() + 1, nullptr));

		vList.insertVertex(newVertex);
	}

	void eraseVertex(int vertexId) {
		Vertex* delVertex = vList.findVertex(vertexId);

		if (delVertex == nullptr)
			return;

		int matrixId = delVertex->matrixId;

		for (int i = 0; i < EdgeMatrix.size(); i++) {
			if (i != matrixId) {
				if (EdgeMatrix[i][matrixId] != nullptr)
					eList.eraseEdge(EdgeMatrix[i][matrixId]);

				EdgeMatrix[i].erase(EdgeMatrix[i].begin() + matrixId);
			}
		}

		EdgeMatrix.erase(EdgeMatrix.begin() + matrixId);
		vList.eraseVertex(delVertex);
	}

	void insertEdge(int srcVertexId, int dstVertexId) {
		Vertex* src = vList.findVertex(srcVertexId);
		Vertex* dst = vList.findVertex(dstVertexId);

		int srcMatrixId = src->matrixId;
		int dstMatrixId = dst->matrixId;

		if (EdgeMatrix[srcMatrixId][dstMatrixId] != nullptr ||
			EdgeMatrix[dstMatrixId][srcMatrixId] != nullptr) {
			cout << "Exist\n";
			return;
		}

		Edge* newEdge = new Edge(src, dst);
		eList.insertEdge(newEdge);
		EdgeMatrix[srcMatrixId][dstMatrixId] = newEdge;
		EdgeMatrix[dstMatrixId][srcMatrixId] = newEdge;
	}

	void eraseEdge(int srcVertexId, int dstVertexId) {
		Vertex* src = vList.findVertex(srcVertexId);
		Vertex* dst = vList.findVertex(dstVertexId);

		int srcMatrixId = src->matrixId;
		int dstMatrixId = dst->matrixId;

		if (EdgeMatrix[srcMatrixId][dstMatrixId] == nullptr ||
			EdgeMatrix[dstMatrixId][srcMatrixId] == nullptr) {
			cout << "None\n";
			return;
		}

		Edge* delEdge = EdgeMatrix[srcMatrixId][dstMatrixId];
		eList.eraseEdge(delEdge);    // modified
		EdgeMatrix[srcMatrixId][dstMatrixId] = nullptr;
		EdgeMatrix[dstMatrixId][srcMatrixId] = nullptr;
	}

	void print_Adjacent(int vertexId) {
		Vertex* curVertex = vList.findVertex(vertexId);
		int matrixId = curVertex->matrixId;

		for (int i = 0; i < EdgeMatrix[matrixId].size(); i++) {
			if (EdgeMatrix[matrixId][i] != nullptr)
				cout << vList.findVertex_by_matrixId(i)->vertexId << ' ';
		}
	}

	void minEdgeVertex() {
		int id = 10001;
		int min = 10000;

		for (int i = 0; i < EdgeMatrix.size(); i++) {
			int cnt = 0;

			for (int j = 0; j < EdgeMatrix[i].size(); j++) {
				if (EdgeMatrix[i][j] != nullptr)
					cnt++;
			}

			if (cnt < min) {
				int vertexId = vList.findVertex_by_matrixId(i)->vertexId;
				
				id = vertexId;
				min = cnt;
			}

			if (cnt == min) {
				int vertexId = vList.findVertex_by_matrixId(i)->vertexId;

				if (vertexId < id)
					id = vertexId;
			}
		}

		if (min == 0 || id == 10001) {
			cout << "-1\n";
			return;
		}

		cout << id << '\n';
	}
};

int main() {
	Graph g;
	int T; cin >> T;

	while (T--) {
		string cmd; cin >> cmd;

		if (cmd == "insertVertex") {
			int s; cin >> s;
			g.insertVertex(s);
		}

		else if (cmd == "insertEdge") {
			int s, d; cin >> s >> d;
			g.insertEdge(s, d);
		}

		else if (cmd == "eraseEdge") {
			int s, d; cin >> s >> d;
			g.eraseEdge(s, d);
		}

		else if (cmd == "isAdjacentOdd") {
			int s; cin >> s;
			g.isAdjacentOdd(s);
		}

		else if (cmd == "minEdgeVertex") {
			g.minEdgeVertex();
		}
	}
}
