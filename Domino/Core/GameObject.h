#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "../Domino.h"

namespace Domino {
	using std::shared_ptr;
	using std::vector;

	class Component;

	class GameObject {
	public:
		GameObject() {}
		~GameObject() {
			onDestroy();
		}

		void AddComponent(shared_ptr<Component> comp);

		/** Callbacks **/
		void init();

		void awake();

		void start();

		void render();

		void update();

		void onDestroy();
	private:
		vector<shared_ptr<Component>> _components;
	};
}

#endif