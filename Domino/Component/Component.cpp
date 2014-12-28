#include "../Domino.h"

namespace Domino {
	Component::~Component() {
		if (gameObject) {
			//gameObject->RemoveComponent(shared_ptr<Component>(this));
		}
	}

	void Component::setGameObject(shared_ptr<GameObject> gameObject) {
		this->gameObject = gameObject;
	}
}