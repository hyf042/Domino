#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "../Domino.h"

namespace Domino {
	using std::shared_ptr;

	class Component : public Object {
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

		// Invoke when scene start
		virtual void startAll() {}
		// Invoke when component is created
		virtual void awake() {}
		// Invoke before the first frame of component
		virtual void start() {}
		// Invoke every frame
		virtual void update() {}
	};
}

#endif