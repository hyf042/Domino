#include "../Domino.h"

namespace Domino {
	vector<shared_ptr<GameObject> > GameObject::destroyQueue;
	vector<shared_ptr<Component> > GameObject::startQueue;

	GameObject::GameObject() {
		static int gameObjectCnt = 0;
		name = "GameObject" + Strings::int2Str(gameObjectCnt++);
		transform = shared_ptr<Transform>(new Transform());
		AddComponent(transform);
		active = true;
	}
	GameObject::~GameObject() {
		transform->setParent(nullptr);
	}

	shared_ptr<Component> GameObject::AddComponent(shared_ptr<Component> comp) {
		if (std::find(components.begin(), components.end(), comp) != components.end()) {
			return nullptr;
		}

		startQueue.push_back(comp);
		comp->setGameObject(shared_from_this());

		components.push_back(comp);

		const type_info &typeinfo = typeid(*comp);
		if(typeinfo==typeid(Renderer)
			||typeinfo==typeid(MeshRenderer))
			renderer = shared_ptr<Renderer>((Renderer*)comp.get());

		return comp;
	}
	void GameObject::RemoveComponent(shared_ptr<Component> comp) {
		if (comp == transform) {
			return;
		}
		auto iter = std::find(components.begin(), components.end(), comp);
		if (iter != components.end()) {
			components.erase(iter);
		}
	}

	/** Callbacks **/
	void GameObject::init() {
		for (auto comp : components) {
			comp->init();
		}
	}

	void GameObject::start() {
		for (auto comp : components) {
			comp->start();
		}
	}

	void GameObject::render() {
		if (renderer) {
			renderer->render();
		}

		for (auto obj : transform->getChildren()) {
			obj->getGameObject()->render();
		}
	}

	void GameObject::update() {
		for (auto comp : components) {
			comp->update();
		}
	}

	void GameObject::doStart() {
		while (!startQueue.empty()) {
			(*startQueue.rbegin())->start();
			startQueue.pop_back();
		}
	}
	void GameObject::doDestroy() {
		while (!destroyQueue.empty()) {
			shared_ptr<GameObject> obj = (*destroyQueue.rbegin());
			destroyQueue.pop_back();
			obj->getTransform()->setParent(shared_ptr<Transform>());
		}
	}
	void GameObject::destroy(shared_ptr<GameObject> obj) {
		if (std::find(destroyQueue.begin(), destroyQueue.end(), obj) == destroyQueue.end()) {
			return;
		}
		destroyQueue.push_back(obj);
	}
	shared_ptr<GameObject> GameObject::createNew() {
		return shared_ptr<GameObject>(new GameObject());
	}
}