#include "../Domino/Domino.h"
using namespace Domino;

class Movable : public Behaviour {
public:
	void update() override {
		if (Input::instance()->getKeyDown('a')) {
			getTransform()->localRotation.y -= Time::deltaTime / 5 * Mathf::PI;
		}
		if (Input::instance()->getKeyDown('d')) {
			getTransform()->localRotation.y += Time::deltaTime / 5 * Mathf::PI;
		}
		if (Input::instance()->getKeyDown('w')) {
			getTransform()->localRotation.x += Time::deltaTime / 5 * Mathf::PI;
		}
		if (Input::instance()->getKeyDown('s')) {
			getTransform()->localRotation.x -= Time::deltaTime / 5 * Mathf::PI;
		}
		if (Input::instance()->getKeyPressed('n')) {
			auto renderer = gameObject->getComponent<MeshRenderer>();
			renderer->setIsWireframe(!renderer->getIsWireframe());
		}
	}
};
