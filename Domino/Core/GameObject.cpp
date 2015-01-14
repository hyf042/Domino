#include "../Domino.h"

namespace Domino {
	vector<shared_ptr<GameObject> > GameObject::destroyQueue;
	vector<shared_ptr<Component> > GameObject::startQueue;

	GameObject::GameObject() {
		static int gameObjectCnt = 0;
		name = "GameObject" + Strings::int2Str(gameObjectCnt++);
		active = true;
	}
	GameObject::~GameObject() {
		transform->setParent(nullptr);
	}

	shared_ptr<Camera> GameObject::getCamera() const {
		if (camera) {
			return camera;
		} else {
			return Camera::getMainCamera();
		}
	}

	shared_ptr<Component> GameObject::addComponent(shared_ptr<Component> comp) {
		if (std::find(components.begin(), components.end(), comp) != components.end()) {
			return nullptr;
		}

		startQueue.push_back(comp);
		comp->setGameObject(shared_from_this());

		components.push_back(comp);

		const type_info &typeinfo = typeid(*comp);
		if (typeinfo==typeid(Renderer)
			||typeinfo==typeid(MeshRenderer)) {
			renderer = std::dynamic_pointer_cast<Renderer>(comp);
		} else if (typeinfo==typeid(Camera)) {
			camera = std::dynamic_pointer_cast<Camera>(comp);
			Camera::setMainCamera(camera);
		}

		comp->awake();
		return comp;
	}
	void GameObject::removeComponent(shared_ptr<Component> comp) {
		if (comp == transform) {
			return;
		}
		auto iter = std::find(components.begin(), components.end(), comp);
		if (iter != components.end()) {
			components.erase(iter);
		}
	}

	void GameObject::initComponents() {
		transform = shared_ptr<Transform>(new Transform());
		auto scene = Application::instance()->getActiveScene();
		if (scene && scene->getRootObj()) {
			transform->setParent(scene->getRootObj()->getTransform());
		}
		addComponent(transform);
	}

	void GameObject::updateTransform() {
		getTransform()->updateTransform();
		for (auto obj : transform->getChildren()) {
			obj->getGameObject()->updateTransform();
		}
	}

	/** Callbacks **/
	void GameObject::startAll() {
		if (!active) {
			return;
		}

		for (auto comp : components) {
			comp->startAll();
		}

		for (auto obj : transform->getChildren()) {
			obj->getGameObject()->startAll();
		}
	}

	void GameObject::render() {
		if (!active) {
			return;
		}

		if (renderer) {
			renderer->render();
		}

		for (auto obj : transform->getChildren()) {
			obj->getGameObject()->render();
		}
	}

	void GameObject::update() {
		if (!active) {
			return;
		}

		for (auto comp : components) {
			comp->update();
		}

		for (auto obj : transform->getChildren()) {
			obj->getGameObject()->update();
		}
	}

	/** static methods **/
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
			obj->getTransform()->setParent(nullptr);
			// TODO(yifeng): solve cyclic reference between GameObject & Component.
		}
	}
	void GameObject::destroy(shared_ptr<GameObject> obj) {
		if (std::find(destroyQueue.begin(), destroyQueue.end(), obj) != destroyQueue.end()) {
			return;
		}
		destroyQueue.push_back(obj);
	}

	shared_ptr<GameObject> GameObject::createNew() {
		auto obj = shared_ptr<GameObject>(new GameObject());
		obj->initComponents();
		return obj;
	}
}