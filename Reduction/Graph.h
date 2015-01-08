#include "../Domino/Domino.h"

namespace Reduction {

	using Domino::Vector3;
	using std::vector;
	using std::shared_ptr;
	
	class Triangle;

	class Vertex {
	public:
		Vector3 position;
		int id;
		vector<shared_ptr<Vertex>> neighbor; // adjacent vertices
		vector<shared_ptr<Triangle>> face; // adjacent triangles
		float cost;
		shared_ptr<Vertex> collapse;

		Vertex(Vector3 v, int id);
		~Vertex();

		void removeIfNonNeighbor(shared_ptr<Vertex> v);
		void addIfNonNeighbor(shared_ptr<Vertex> v);
	};

	class Triangle : public std::enable_shared_from_this<Triangle> {
	public:
		shared_ptr<Vertex> vertex[3];
		Vector3 normal;

		Triangle(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2, shared_ptr<Vertex> v3);
		~Triangle();

		void computeNormal();
		void replaceVertex(shared_ptr<Vertex> vold, shared_ptr<Vertex> vnew);
		bool hasVertex(shared_ptr<Vertex> v) const;
	};

	class Graph {
	public:
		vector<shared_ptr<Vertex>> vertices;
		vector<shared_ptr<Triangle>> triangles;

		// The cost we collapse u to v
		float computeEdgeCollapseCost(shared_ptr<Vertex> u, shared_ptr<Vertex> v);
		// Calculate the least cost edge for vertex v
		void computeEdgeCostAtVertex(shared_ptr<Vertex> v);
		// Collapse the edge by moving u to v
		void collapse(shared_ptr<Vertex> u, shared_ptr<Vertex> v);

		void createGraph(const vector<Vector3>& vertices, const vector<uint32>& elements);

		Graph();
		~Graph();

	private:
		void deleteVertex(shared_ptr<Vertex> v);
		void deleteTriangle(shared_ptr<Triangle> t);
		// Add a triangle if it has 3 different vertices
		void addTriangle(int vi1, int vi2, int vi3);
		static bool checkDuplicate(const Vector3& a, const Vector3& b);
	};
	
}