#include "../../Domino.h"

namespace Domino {

	shared_ptr<Camera> Camera::mainCamera = NULL;

	Camera::Camera() {
		projection = Projection::Perspective;

		nearClipPlane = 0.1f;
		farClipPlane = 10000.0f;
		fieldOfView = 45.0f;
		viewport = Rect(0, 0, 1, 1);
	}

	glm::mat4 Camera::getProjectionMatrix() const {
		if (projection == Perspective) {
			return glm::perspective(
				fieldOfView, 
				(float)(viewport.getWidth() * Application::instance()->getWidth()) / 
					(viewport.getHeight() * Application::instance()->getHeight()), 
				nearClipPlane, 
				farClipPlane);
		} else {
			return glm::ortho(viewport.x, viewport.y, viewport.w, viewport.z);
		}
	}

	glm::mat4 Camera::getViewMatrix() const {
		auto transform = gameObject->getTransform();

		return glm::lookAt(
			(glm::vec3)transform->position(),
			(glm::vec3)transform->forward(),
			(glm::vec3)transform->up()
		);
	}
}