#include "Graph.h"

namespace Reduction {

	using std::min;
	using std::max;

	Vertex::Vertex(Vector3 v, int id) {
		position = v;
		this->id = id;
		neighbor.clear();
		face.clear();
		cost = 0.0f;
		collapse = nullptr;
	}

	Vertex::~Vertex() {
		static int cnt = 0;
		cnt++;
		printf("%d vertex released\n", cnt);
	}

	void Vertex::removeIfNonNeighbor(shared_ptr<Vertex> v) {
		for (int i = 0; i < face.size(); i++) {
			if (face[i]->hasVertex(v)) {
				return;
			}
		}
		for (auto i = neighbor.begin(); i != neighbor.end(); i++) {
			if (*i == v) {
				neighbor.erase(i);
				break;
			}
		}
	}

	void Vertex::addIfNonNeighbor(shared_ptr<Vertex> v) {
		for (auto i : neighbor) {
			if (i == v) {
				return;
			}
		}
		neighbor.push_back(v);
	}

	Triangle::Triangle(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2, shared_ptr<Vertex> v3) {
		vertex[0] = v1;
		vertex[1] = v2;
		vertex[2] = v3;
		computeNormal();
	}

	Triangle::~Triangle() {
	}

	void Triangle::computeNormal() {
		normal = Vector3::cross(vertex[1]->position - vertex[0]->position, vertex[2]->position - vertex[0]->position);
		normal = normal.normalize();
	}

	void Triangle::replaceVertex(shared_ptr<Vertex> vold, shared_ptr<Vertex> vnew) {
		for (int i = 0; i < 3; i++) {
			if (vertex[i] == vold) {
				vertex[i] = vnew;
				vnew->face.push_back(shared_from_this());
				break;
			}
		}
		for (int i = 0; i < 3; i++) {
			if (vertex[i] != vold) {
				vertex[i]->removeIfNonNeighbor(vold);
				vertex[i]->addIfNonNeighbor(vnew);
				vnew->addIfNonNeighbor(vertex[i]);
				// didn't check vold's neigbbor, anyway it will be deleted
			}
		}
		computeNormal();
	}

	bool Triangle::hasVertex(shared_ptr<Vertex> v) const {
		return vertex[0] == v || vertex[1] == v || vertex[2] == v;
	}

	Graph::Graph() {
	}

	Graph::~Graph() {
	}

	void Graph::createGraph(const vector<Vector3>& ver, const vector<uint32>& elements) {
		vertices.clear();
		triangles.clear();

		for (int i = 0; i < ver.size(); i++) {
			vertices.push_back(shared_ptr<Vertex>(new Vertex(ver[i], i)));
		}

		for (int i = 0; i < elements.size() / 3; i++) {
			triangles.push_back(shared_ptr<Triangle>(new Triangle(vertices[elements[3*i]], vertices[elements[3*i+1]], vertices[elements[3*i+2]])));
		}

		// generate neighbor information
		for (int i = 0; i < triangles.size(); i++) {
			for (int j = 0; j < 3; j++) {
				triangles[i]->vertex[j]->face.push_back(triangles[i]);
				for (int k = 0; k < 3; k++) {
					if (j != k) {
						triangles[i]->vertex[j]->addIfNonNeighbor(triangles[i]->vertex[k]);
						triangles[i]->vertex[k]->addIfNonNeighbor(triangles[i]->vertex[j]);
					}
				}
			}
		}

		// compute the initial cost
		for (int i = 0; i < vertices.size(); i++) {
			computeEdgeCostAtVertex(vertices[i]);
		}
	}

	float Graph::computeEdgeCollapseCost(shared_ptr<Vertex> u, shared_ptr<Vertex> v) {
		float edgeLength = (v->position - u->position).magnitude();
		float curvature = 0.0f;

		// Find the side triangles which have edge u->v
		vector<shared_ptr<Triangle>> sides;
		for (uint32 i = 0; i < u->face.size(); i++) {
			if (u->face[i]->hasVertex(v)) {
				sides.push_back(u->face[i]);
			}
		}

		for (uint32 i = 0; i < u->face.size(); i++) {
			float mincurv=1;
			for (uint32 j = 0; j < sides.size(); j++) {
				// use dot product of face normals
				float dotprod = Vector3::dot(u->face[i]->normal, sides[j]->normal);
				if (dotprod < 0) {
					dotprod = -dotprod;
				}
				mincurv = min(mincurv, (1-dotprod) / 2.0f);
			}
			curvature = max(curvature, mincurv);
		}

		return edgeLength * curvature;
	}

	void Graph::computeEdgeCostAtVertex(shared_ptr<Vertex> v) {
		if (v->neighbor.size() == 0) {
			v->collapse = nullptr;
			v->cost = -0.01f;
			return;
		}
		v->cost = 1000000;
		v->collapse = nullptr;
		// serach all the neighbor edges for "least cost" edge
		for (uint32 i = 0; i < v->neighbor.size(); i++) {
			float c = computeEdgeCollapseCost(v, v->neighbor[i]);
			if (c < v->cost) {
				v->cost = c;
				v->collapse = v->neighbor[i];
			}
		}
	}

	void Graph::collapse(shared_ptr<Vertex> u, shared_ptr<Vertex> v) {
		if (v == nullptr) {
			deleteVertex(u);
			return;
		}
		// record u's neighbors
		auto temp = u->neighbor;
		// delete triangles on edge uv
		for (int i = u->face.size() - 1; i >= 0; i--) {
			if (u->face[i]->hasVertex(v)) {
				deleteTriangle(u->face[i]);
			}
		}
		// update remaining triangles to have v instead of u
		for (int i = u->face.size() - 1; i >= 0; i--) {
			u->face[i]->replaceVertex(u, v);
		}
		deleteVertex(u);
		// recompute the edge collapse costs
		for (int i = 0; i < temp.size(); i++) {
			computeEdgeCostAtVertex(temp[i]);
		}
	}

	void Graph::deleteVertex(shared_ptr<Vertex> v) {
		for (auto i = vertices.begin(); i != vertices.end(); i++) {
			if (*i == v) {
				vertices.erase(i);
				break;
			}
		}
	}

	void Graph::deleteTriangle(shared_ptr<Triangle> t) {
		for (int i = 0; i < 3; i++) {
			for (auto j = t->vertex[i]->face.begin(); j != t->vertex[i]->face.end(); j++) {
				if (*j == t) {
					t->vertex[i]->face.erase(j);
					break;
				}
			}
		}

		for (auto i = triangles.begin(); i != triangles.end(); i++) {
			if (*i == t) {
				triangles.erase(i);
				break;
			}
		}

		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++) {
				if (i != j) {
					t->vertex[i]->removeIfNonNeighbor(t->vertex[j]);
				}
			}
	}
}