#pragma once

#include "Graph.h"
#include "../Domino/Domino.h"
using namespace Domino;

class PolyRed : public Behaviour {
public:
	Vector3 mousePosition;
	shared_ptr<Mesh> mesh;
	shared_ptr<Mesh> clonedMesh;
	shared_ptr<Reduction::Graph> graph;

	void start() override;
	void update() override;

private:
	shared_ptr<Reduction::Vertex> findMinCostVertex();

};
