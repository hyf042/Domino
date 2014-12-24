#include "GameObject.h"

namespace Domino {
	void GameObject::AddComponent(shared_ptr<Component> comp) {
		_components.push_back(comp);
	}

	/** Callbacks **/
	void GameObject::init() {
		for (auto comp : _components) {
			comp->init();
		}
	}

	void GameObject::start() {
		for (auto comp : _components) {
			comp->start();
		}
	}

	void GameObject::update() {
		for (auto comp : _components) {
			comp->update();
		}
	}
}