#ifndef __SCENE_H__
#define __SCENE_H__

#include "../Domino.h"

namespace Domino {
	class Scene : public Object {
	private:
		shared_ptr<GameObject> rootObj;
	public:
		Scene() {
			rootObj = GameObject::createNew();
		}
		~Scene() {}

		shared_ptr<GameObject> getRootObj() {
			return rootObj;
		}

		void init();
		void start();
		void render();
		void update();
	};
}

#endif