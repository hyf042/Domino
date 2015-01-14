#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "../../Domino.h"

namespace Domino {
	class Camera : public Component {
		friend class GameObject;

		static shared_ptr<Camera> mainCamera;
	public:
		enum Projection {
			Perspective, Orthogonal
		};

		Projection projection;

		float nearClipPlane;
		float farClipPlane;
		float fieldOfView;

		Rect viewport;

		Camera();
		virtual ~Camera() {}

		glm::mat4 getProjectionMatrix() const;
		glm::mat4 getViewMatrix() const;
		glm::mat4 getCameraMatrix() const {
			return getProjectionMatrix() * getViewMatrix();
		}
		static shared_ptr<Camera> getMainCamera() {
			return mainCamera;
		}
		static void setMainCamera(shared_ptr<Camera> camera) {
			if (!mainCamera) {
				mainCamera = camera;
			}
		}
	};
}

#endif