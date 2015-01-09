#include "../Domino/Domino.h"
using namespace Domino;

class Movable : public Behaviour {
public:
	void update() override {
		if (Input::instance()->getKeyDown('z')) {
			getTransform()->localRotation.y -= Time::deltaTime / 5 * Mathf::PI;
		}
		if (Input::instance()->getKeyDown('x')) {
			getTransform()->localRotation.y += Time::deltaTime / 5 * Mathf::PI;
		}
	}
};
