#include "../Domino.h"

namespace Domino {
	void Scene::init() {
		rootObj->init();
	}

	void Scene::start() {
		rootObj->start();
	}

	void Scene::render() {
		rootObj->render();
	}

	void Scene::update() {
		rootObj->update();
	}
}