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
		if (vList.findVertex(vertexId) != nullptr)
			return;

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
			EdgeMatrix[dstMatrixId][srcMatrixId] != nullptr)
			return;

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
			EdgeMatrix[dstMatrixId][srcMatrixId] == nullptr)
			return;

		Edge* delEdge = EdgeMatrix[srcMatrixId][dstMatrixId];
		eList.eraseEdge(delEdge);    // modified
		EdgeMatrix[srcMatrixId][dstMatrixId] = nullptr;
		EdgeMatrix[dstMatrixId][srcMatrixId] = nullptr;
	}

	void maskAdjacentVertices(int vertexId, vector<bool>& v) {
		Vertex* curVertex = vList.findVertex(vertexId);
		int matrixId = curVertex->matrixId;

		for (int i = 0; i < EdgeMatrix[matrixId].size(); i++) {
			if (EdgeMatrix[matrixId][i] != nullptr) {
				v[i + 1] = true;
			}
		}

	}
};

int main() {
	Graph g;
	int N, M, D; cin >> N >> M >> D;

	vector<int> denied;

	for (int i = 0; i < D; i++) {
		int s; cin >> s;
		denied.push_back(s);
	}

	for (int i = 0; i < N; i++) {
		g.insertVertex(i + 1);
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int is_friend; cin >> is_friend;

			if (is_friend)
				g.insertEdge(i + 1, j + 1);
		}
	}

	for (int i = 0; i < M; i++) {
		int K, S; cin >> K >> S;
		vector<bool> result_table(N + 1, false);

		g.maskAdjacentVertices(K, result_table);

		if (S == 2) {
			for (int i = 1; i <= N; i++) {
				if (result_table[i])
					g.maskAdjacentVertices(i, result_table);
			}
		}
		result_table[K] = false;

		for (int i = 0; i < D; i++) {
			if (result_table[denied[i]])
				result_table[denied[i]] = false;
		}

		bool is_empty = true;

		for (int i = 1; i <= N; i++) {
			if (result_table[i]) {
				cout << i << ' ';
				is_empty = false;
			}
		}

		if (is_empty)
			cout << 0;

		cout << '\n';
	}
}
