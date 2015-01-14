#include "../Domino.h"

namespace Domino {
	Transform::Transform() {
		localPosition = Vector3(0, 0, 0);
		localRotation = Vector3(0, 0, 0);
		localScale = Vector3(1, 1, 1);
	}

	void Transform::updateTransform() {
		if (!parent) {
			worldPosition = localPosition;
			worldRotation = localRotation;
			worldScale = localScale;
		}
		else {
			worldPosition = parent->getTransform()->position() + localPosition;
			worldRotation = parent->getTransform()->rotation() + localRotation;
			worldScale = parent->getTransform()->scale() * localScale;
		}

		// Calculate transformation matrix
		matrix = glm::mat4(1.0f);
		matrix = glm::translate(matrix, (glm::vec3)worldPosition);
		matrix = glm::scale(matrix, (glm::vec3)worldScale);
		matrix = matrix * Quaternion::euler(worldRotation);
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

	Vector3 Transform::forward() const {
		Vector3 forwardTo = (glm::vec3)(matrix * glm::vec4(0, 0, 1, 1));
		Vector3 zeroAt = (glm::vec3)(matrix * glm::vec4(0, 0, 0, 1));
		return (forwardTo - zeroAt).normalize();
	}

	Vector3 Transform::up() const {
		Vector3 upTo = (glm::vec3)(matrix * glm::vec4(0, 1, 0, 1));
		Vector3 zeroAt = (glm::vec3)(matrix * glm::vec4(0, 0, 0, 1));
		return (upTo - zeroAt).normalize();
	}
}