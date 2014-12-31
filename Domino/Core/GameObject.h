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

	private:
		GameObject();
	public:
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

		shared_ptr<Component> addComponent(shared_ptr<Component> comp);
		template<typename T>
		shared_ptr<T> addComponent() {
			auto t = shared_ptr<T>(new T());
			addComponent(t);
			return t;
		}
		void removeComponent(shared_ptr<Component> comp);
		template<typename T>
		shared_ptr<T> getComponent() {
			for (auto comp : components) {
				if (typeid(*comp.get()) == typeid(T)) {
					return std::dynamic_pointer_cast<T>(comp);
				}
			}
			return nullptr;
		}

		/** Callbacks **/
		void startAll();

		void update();

		void render();

		void updateTransform();

	private:
		void initComponents();

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