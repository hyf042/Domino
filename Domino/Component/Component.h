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

		void setGameObject(shared_ptr<GameObject> gameObject);
		shared_ptr<GameObject> getGameObject() const {
			return gameObject;
		}

		virtual void init() {}
		virtual void start() {}
		virtual void update() {}
	};
}

#endif