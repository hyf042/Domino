#ifndef __INPUT_H__

#include <set>
#include "../Domino.h"

namespace Domino {
	class Input {
		friend Application;

		int mouseX;
		int mouseY;
		std::set<unsigned char> keyDown;
		std::set<unsigned char> keyPress;

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

		bool getKeyPressed(unsigned char key) const {
			return keyPress.find(key) != keyPress.end();
		}

		void afterUpdate() {
			keyPress.clear();
		}

	private:
		void mouseCB(int button, int state, int x, int y) {
			mouseX = x;
			mouseY = y;
		}

		void keyboardCB(unsigned char key, int x, int y) {
			if (keyDown.find(key) == keyDown.end()) {
				keyPress.insert(key);
			}
			keyDown.insert(key);
		}

		void keyboardUpCB(unsigned char key, int x, int y) {
			keyDown.erase(key);
		}
	};
}

#endif