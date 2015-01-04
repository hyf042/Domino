#include "../Domino/Domino.h"
using namespace Domino;

class Movable : public Behaviour {
public:
	void update() override {
		getTransform()->localRotation.y = Mathf::fmod(Mathf::PI * 2 * Time::time / 5, Mathf::PI * 2);
	}
};
