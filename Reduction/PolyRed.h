#pragma once

#include "Graph.h"
#include "VertexPicker.h"
#include "../Domino/Domino.h"
using namespace Domino;

class PolyRed : public MonoBehaviour {
	Vector2 lastMousePos;
public:
	shared_ptr<Mesh> mesh;
	shared_ptr<Mesh> clonedMesh;
	shared_ptr<Reduction::Graph> graph;

	void start() override;
	void update() override;

private:
	shared_ptr<Reduction::Vertex> findMinCostVertex();
	static Vector3 getMouseGlobalPosition(int mousex, int mousey);
	static float calcPenalty(float distant);

	
};
