#include "../Domino.h"

namespace Domino {
	Transform::Transform() {
		localPosition = Vector3(0, 0, 0);
		localRotation = Vector3(0, 0, 0);
		localScale = Vector3(1, 1, 1);
	}

	void Transform::updateTransform() {
		if (!parent) {
			// rootObj do not update
			return;
		}
		worldPosition = parent->getTransform()->position() + localPosition;
		worldRotation = localRotation;
		worldScale = localScale;
	}

	void Transform::addChild(TransformPtr child) {
		if (child->getParent() == shared_from_this()) {
			return;
		}
		child->removeSelf();
		child->parent = shared_from_this();
		children.push_back(child);
	}

	void Transform::removeChild(TransformPtr child) {
		auto iter = std::find(children.begin(), children.end(), child);
		if (iter == children.end()) {
			return;
		}
		children.erase(iter);
		child->parent.reset();
	}

	void Transform::removeSelf() {
		if (parent) {
			parent->removeChild(shared_from_this());
		}
	}

	TransformPtr Transform::find(string name) {
		if (getName() == name) {
			return shared_from_this();
		}
		for (auto transform : children) {
			auto ptr = transform->find(name);
			if (ptr) {
				return ptr;
			}
		}
		return nullptr;
	}
	TransformPtr Transform::findChild(string name) {
		for (auto transform : children) {
			if (transform->getName() == name) {
				return transform;
			}
		}
		return nullptr;
	}
	bool Transform::isChildOf(TransformPtr transform) {
		return std::find(children.begin(), children.end(), transform) == children.end();
	}
}