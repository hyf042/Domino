#pragma once

#include "Graph.h"
#include "../Domino/Domino.h"
using namespace Domino;

struct VertexContainer {
	std::shared_ptr<Reduction::Vertex> vertex;
	float dist;
	int groupId;
	bool picked;

	VertexContainer(std::shared_ptr<Reduction::Vertex> v, float d);
};

class VertexPicker {
public:
	vector<VertexContainer> container;
	vector<int> pickNums;
	int pickCount;
	int currentGroup;

	void clear();
	void addVertex(std::shared_ptr<Reduction::Vertex> vertex, float dist);
	void beginPick(int pickNum, const vector<float>& groupInfo, const vector<float>& pickPercent);
	void beginPick(float pickRatio, const vector<float>& groupInfo, const vector<float>& pickPercent);
	std::shared_ptr<Reduction::Vertex> Pick();

	VertexPicker();
	~VertexPicker();

	bool isPickFinished() const;

	static bool cmp(const VertexContainer& a, const VertexContainer& b);
private:
	
};

