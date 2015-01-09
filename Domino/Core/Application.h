#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "../Domino.h"

namespace Domino {
	using std::shared_ptr;
	using std::string;

	class Application {
		shared_ptr<Scene> activeScene;
		int width;
		int height;

		Application() {}
	public:
		static shared_ptr<Application> instance() {
			static shared_ptr<Application> m_instance(new Application());
			return m_instance;
		}

		virtual ~Application() {}

		int getWidth() const {
			return width;
		}
		int getHeight() const {
			return height;
		}

		void setUp(string title, int width, int height, int argc, char **argv);
		void run();

		shared_ptr<Scene> getActiveScene() {
			return activeScene;
		}

	protected:
		virtual void onRender(void);
		virtual void onUpdate(void);
	private:
		void createContext(string title, int width, int height, int argc, char **argv);

		void render();
		void update();

		static void drawCB();
		static void reshapeCB(int width, int height);
		static void timerCB(int ms);
		static void mouseCB(int button, int state, int x, int y);
		static void keyboardCB(unsigned char key, int x, int y);
		static void keyboardUpCB(unsigned char key, int x, int y);
	};
}

#endif