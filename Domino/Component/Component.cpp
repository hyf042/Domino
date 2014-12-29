#include "../Domino.h"

namespace Domino {
	Component::~Component() {}

	void Component::setGameObject(shared_ptr<GameObject> gameObject) {
		this->gameObject = gameObject;
	}
}