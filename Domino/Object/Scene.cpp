#include "../Domino.h"

namespace Domino {
	void Scene::startAll() {
		rootObj->startAll();
	}

	void Scene::render() {
		rootObj->render();
	}

	void Scene::update() {
		rootObj->updateTransform();

		rootObj->update();
	}
}