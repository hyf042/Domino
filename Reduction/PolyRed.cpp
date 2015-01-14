#include "PolyRed.h"

using namespace Reduction;

void PolyRed::start() {
	mesh = getGameObject()->getComponent<MeshFilter>()->getMesh();
	clonedMesh = mesh->clone();
	graph = shared_ptr<Graph>(new Graph());
}

void PolyRed::update() {
	// from model to view:
	//   proj * view * model * p = p'
	// from view to model:
	//   model-1  * view-1 * proj-1 * p' = p
	/*auto modelMatrix = gameObject->getTransform()->getModelMatrix();
	auto viewMatrix = gameObject->getCamera()->getViewMatrix();
	auto projMatrix = gameObject->getCamera()->getProjectionMatrix();
	auto invModelMatrix = glm::inverse(modelMatrix);*/

	Vector2 mousePos(
		Input::instance()->getMouseX(),
		Input::instance()->getMouseY());

	if (mousePos == lastMousePos) {
		return;
	}
	lastMousePos = mousePos;

	vector<Vector3> vertices;
	vector<Color> colors;
	vector<Vector2> uvs;
	vector<uint32> elements;
	clonedMesh->getOriginVerticesData(vertices, colors, uvs, elements);

	graph->createGraph(vertices, elements);
	VertexPicker picker;
	Vector3 gMousePos = getMouseGlobalPosition(mousePos.x, mousePos.y);

	for (int i = 0; i < graph->vertices.size(); i++) {
		Vector3 tPos = graph->vertices[i]->position;
		glm::vec4 originPos(tPos.x, tPos.y, tPos.z, 1.0f);
		glm::vec4 globalPos = getTransform()->getModelMatrix() * originPos;
		Vector3 truePos(globalPos.x, globalPos.y, globalPos.z);
		picker.addVertex(graph->vertices[i], Vector3::dotToLineDistant(truePos,
			gMousePos, Vector3()));
	}
	float gi[] = {0.2f, 0.5f, 1.0f};
	float pp[] = {0.0f, 0.2f, 1.0f};
	vector<float> groupInfo, pickPercent;
	for (int i = 0; i < 3; i++) {
		groupInfo.push_back(gi[i]);
		pickPercent.push_back(pp[i]);
	}
	picker.beginPick(0.5f, groupInfo, pickPercent);
	while (!picker.isPickFinished()) {
		auto u = picker.Pick();
		if (u != nullptr) {
			graph->collapse(u, u->collapse);
		}
		printf("(%.3f %.3f %.3f)\n", u->position.x, u->position.y, u->position.z);
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

float PolyRed::calcPenalty(float distant) {
	static float penalty[3][2] = {{0.3f, 0.0f}, {1.0f, 2.0f}, {2.0f, 4.0f}};
	for (int i = 0; i < 3; i++) {
		if (distant < penalty[i][0]) {
			return penalty[i][1];
		}
	}
	return penalty[2][1];
}

shared_ptr<Vertex> PolyRed::findMinCostVertex() {
	shared_ptr<Vertex> v = nullptr;
	float c = 1000000;
	Vector3 mousep = getMouseGlobalPosition(
		Input::instance()->getMouseX(),
		Input::instance()->getMouseY());
	
	for (int i = 0; i < graph->vertices.size(); i++) {
		float dist = Vector3::dotToLineDistant(graph->vertices[i]->position, mousep, Vector3());
		//printf("%.3f ", dist);
		float p = calcPenalty(dist);
		float tc = graph->vertices[i]->cost;
		if (tc < c) {
			c = tc;
			v = graph->vertices[i];
		}
	}

	return v;
}

Vector3 PolyRed::getMouseGlobalPosition(int mousex, int mousey) {
	float halfWidth = Application::instance()->getWidth() / 2;
	float halfHeight = Application::instance()->getHeight() / 2;
	float px = (mousex - halfWidth) / halfWidth;
	float py = -(mousey - halfHeight) / halfHeight;
	//float nearDis = 1.0f;
	//float fov = 44.5f;
	//float ratio = 2 * nearDis * 1.442 * Mathf::tan(Mathf::deg2Rad(fov / 2)) / Application::instance()->getHeight();
	//return Vector3(px * ratio, py * ratio, nearDis);
	glm::vec4 screenMouse(px, py, 0.0f, 1.0f);
	glm::vec4 globalMouse = glm::inverse(Camera::getMainCamera()->getViewMatrix()) *
		glm::inverse(Camera::getMainCamera()->getProjectionMatrix()) * screenMouse;
	return Vector3(globalMouse.x, globalMouse.y, globalMouse.z);
}