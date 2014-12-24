#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "../Domino.h"

namespace Domino {
	using std::shared_ptr;
	using std::string;

	class Mesh;

	class Application {
		Application() {}
	public:
		static shared_ptr<Application> instance() {
			static shared_ptr<Application> m_instance(new Application());
			return m_instance;
		}

		virtual ~Application() {
			onDestroy();
		}

		void setUp(string title, int width, int height, int argc, char **argv);
		void run();

	protected:
		virtual void onRender(void);
		virtual void onDestroy();
		virtual void onInit();
	private:
		shared_ptr<Mesh> mesh;
	private:
		void createContext(string title, int width, int height, int argc, char **argv);

		void createGlewContext();

		void render();

		static void drawFunc();
	};
}

#endif