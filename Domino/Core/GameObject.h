#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "../Domino.h"

namespace Domino {
	using std::shared_ptr;
	using std::vector;
	using std::queue;

	class Component;
	class Transform;
	class Renderer;

	class GameObject : 
		public Object, 
		public std::enable_shared_from_this<GameObject> {
	protected:
		string name;
		shared_ptr<Transform> transform;
		shared_ptr<Renderer> renderer;
		vector<shared_ptr<Component> > components;
		bool active;
	public:
		GameObject();
		virtual ~GameObject();

		string getName() const {
			return name;
		}
		shared_ptr<Transform> getTransform() {
			return transform;
		}
		shared_ptr<Renderer> getRenderer() {
			return renderer;
		}

		void setActive(bool active) {
			this->active = active;
		}
		bool isActive() {
			return active;
		}

		shared_ptr<Component> AddComponent(shared_ptr<Component> comp);
		template<typename T>
		shared_ptr<T> AddComponent() {
			T* t = new T();
			AddComponent(shared_ptr<Component>(t));
			return shared_ptr<T>(t);
		}
		void RemoveComponent(shared_ptr<Component> comp);
		template<typename T>
		shared_ptr<T> GetComponent() {
			for (auto comp : components) {
				if (typeid(*comp.get()) == typeid(T)) {
					return shared_ptr<T>(dynamic_cast<T*>(comp.get()));
				}
			}
			return shared_ptr<T>();
		}

		/** Callbacks **/
		void init();

		void start();

		void update();

		void render();

	public:
		static void doStart();
		static void doDestroy();
		static void destroy(shared_ptr<GameObject> obj);
		static shared_ptr<GameObject> createNew();

	protected:
		static vector<shared_ptr<Component>> startQueue;
		static vector<shared_ptr<GameObject>> destroyQueue;
	};
}

#endif