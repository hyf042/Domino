#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "../Domino.h"

namespace Domino {
	using std::shared_ptr;

	class Component {
	protected:
		shared_ptr<GameObject> gameObject;
	public:
		Component() {}
		virtual ~Component();

		std::string getName() const {
			return gameObject->getName();
		}
		shared_ptr<Transform> getTransform() const {
			return getGameObject()->getTransform();
		}

		void setGameObject(shared_ptr<GameObject> gameObject);
		shared_ptr<GameObject> getGameObject() const {
			return gameObject;
		}

		virtual void awake() {}
		virtual void start() {}
		virtual void update() {}
	};
}

#endif