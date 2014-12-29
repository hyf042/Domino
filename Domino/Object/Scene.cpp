#include "../Domino.h"

namespace Domino {
	void Scene::awake() {
		rootObj->awake();
	}

	void Scene::render() {
		rootObj->render();
	}

	void Scene::update() {
		rootObj->updateTransform();

		rootObj->update();
	}
}