#include "VertexPicker.h"
#include <algorithm>

using std::shared_ptr;

VertexPicker::VertexPicker() {
	clear();
}

VertexPicker::~VertexPicker() {
}

void VertexPicker::clear() {
	container.clear();
	pickNums.clear();
	pickCount = 0;
	currentGroup = 0;
}

void VertexPicker::addVertex(std::shared_ptr<Reduction::Vertex> vertex, float dist) {
	container.push_back(VertexContainer(vertex, dist));
}

void VertexPicker::beginPick(int pickNum, const vector<float>& groupInfo, const vector<float>& pickPercent) {
	std::sort(container.begin(), container.end(), cmp);
	int p = 0;
	for (int i = 0; i < container.size(); i++) {
		while (i > groupInfo[p] * container.size() && p < groupInfo.size() - 1) {
			p++;
		}
		container[i].groupId = p;
	}
	pickNums.resize(groupInfo.size());
	for (int i = 0; i < pickPercent.size() - 1; i++) {
		pickNums[i] = pickPercent[i] * pickNum;
	}
	pickNums[pickPercent.size() - 1] = pickNum;
	pickCount = 0;
	currentGroup = 0;
}

std::shared_ptr<Reduction::Vertex> VertexPicker::Pick() {
	if (isPickFinished()) {
		return nullptr;
	}
	while (pickCount >= pickNums[currentGroup]) {
		currentGroup++;
	}

	int index = 0;
	int cnt = 0;
	float c = 10000000;
	for (auto v : container) {
		if (v.groupId == currentGroup && v.picked == false) {
			if (v.vertex->cost < c) {
				c = v.vertex->cost;
				index = cnt;
			}
		}
		cnt++;
	}

	pickCount++;
	container[index].picked = true;
	return container[index].vertex;
}

void VertexPicker::beginPick(float pickRatio, const vector<float>& groupInfo, const vector<float>& pickPercent) {
	beginPick((int)(pickRatio * container.size()), groupInfo, pickPercent);
}

bool VertexPicker::isPickFinished() const {
	return pickCount >= pickNums[pickNums.size() - 1];
}

bool VertexPicker::cmp(const VertexContainer& a, const VertexContainer& b) {
	return a.dist < b.dist;
}

VertexContainer::VertexContainer(std::shared_ptr<Reduction::Vertex> v, float d) {
	vertex = v;
	dist = d;
	picked = false;
	groupId = -1;
}