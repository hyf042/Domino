#ifndef __INPUT_H__

#include <set>
#include "../Domino.h"

namespace Domino {
	class Input {
		friend Application;

		int mouseX;
		int mouseY;
		std::set<unsigned char> keyDown;

		Input() {}
	public:
		static shared_ptr<Input> instance() {
			static shared_ptr<Input> m_instance(new Input());
			return m_instance;
		}

		int getMouseX() const {
			return mouseX;
		}

		int getMouseY() const {
			return mouseY;
		}

		bool getKeyDown(unsigned char key) const {
			return keyDown.find(key) != keyDown.end();
		}

		void update() {}

	private:
		void mouseCB(int button, int state, int x, int y) {
			mouseX = x;
			mouseY = y;
		}

		void keyboardCB(unsigned char key, int x, int y) {
			keyDown.insert(key);
		}

		void keyboardUpCB(unsigned char key, int x, int y) {
			keyDown.erase(key);
		}
	};
}

#endif