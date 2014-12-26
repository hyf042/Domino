#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "../Domino.h"

namespace Domino {
	using std::shared_ptr;
	using std::string;

	class MeshRenderer;

	class Application {
		Application() {}
	public:
		static shared_ptr<Application> instance() {
			static shared_ptr<Application> m_instance(new Application());
			return m_instance;
		}

		virtual ~Application() {}

		void setUp(string title, int width, int height, int argc, char **argv);
		void run();

	protected:
		virtual void onRender(void);
		virtual void onInit();
	private:
		shared_ptr<MeshRenderer> mesh;
	private:
		void createContext(string title, int width, int height, int argc, char **argv);

		void render();
		void update();

		static void drawCB();
		static void reshapeCB(int width, int height);
		static void timerCB(int ms);
	};
}

#endif