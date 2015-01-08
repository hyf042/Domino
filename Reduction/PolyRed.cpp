#include "PolyRed.h"

using namespace Reduction;

void PolyRed::start() {
	mesh = getGameObject()->getComponent<MeshFilter>()->getMesh();
	clonedMesh = mesh->clone();
	graph = shared_ptr<Graph>(new Graph());
}

void PolyRed::update() {
	vector<Vector3> vertices;
	vector<Color> colors;
	vector<Vector2> uvs;
	vector<uint32> elements;
	clonedMesh->getOriginVerticesData(vertices, colors, uvs, elements);

	graph->createGraph(vertices, elements);
	int desNum = graph->vertices.size() / 2;
	while (graph->vertices.size() > desNum) {
		auto u = findMinCostVertex();
		graph->collapse(u, u->collapse);
	}

	// generate new elements
	vector<Vector3> nvertices;
	vector<Color> ncolors;
	vector<Vector2> nuvs;
	vector<uint32> nelements;
	int cnt = 0;
	for (auto v : graph->vertices) {
		nvertices.push_back(vertices[v->id]);
		ncolors.push_back(colors[v->id]);
		nuvs.push_back(uvs[v->id]);
		v->id = cnt;
		cnt++;
	}
	for (auto t : graph->triangles) {
		for (int j = 0; j < 3; j++) {
			nelements.push_back(t->vertex[j]->id);
		}
	}

	// set the elements back
	mesh->setOriginVerticesData(nvertices, ncolors, nuvs, nelements);
}

shared_ptr<Vertex> PolyRed::findMinCostVertex() {
	shared_ptr<Vertex> v = nullptr;
	float c = 1000000;
	
	for (int i = 0; i < graph->vertices.size(); i++) {
		if (graph->vertices[i]->cost < c) {
			c = graph->vertices[i]->cost;
			v = graph->vertices[i];
		}
	}

	return v;
}