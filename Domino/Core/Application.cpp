#include "../Domino.h"

namespace Domino {
	float targetFPS = 0;

	void Application::setUp(string title, int width, int height, int argc, char **argv) {
		createContext(title, width, height, argc, argv);

		activeScene = shared_ptr<Scene>(new Scene());
	}

	void Application::run() {
		activeScene->init();
		activeScene->start();
		glutMainLoop();
	}

	void Application::onRender(void) {
		activeScene->render();
	}

	void Application::onUpdate(void) {
		activeScene->update();
	}

	void Application::createContext(string title, int width, int height, int argc, char **argv) {
		glutInit(&argc, argv);

		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
		glutInitWindowPosition(50, 25);
		glutInitWindowSize(width, height);

		glutCreateWindow(title.c_str());
		if (targetFPS == 0) {
			targetFPS = 60;
		}
		float targetDeltaTime = 1000/targetFPS;

		glutDisplayFunc(drawCB);
		glutTimerFunc(targetDeltaTime, timerCB, targetDeltaTime);
		glutReshapeFunc(reshapeCB);

		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		}
	}

	void Application::render() {
		glClearColor(0, 0, 0, 1);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		onRender();

		glFlush();
	}

	void Application::update() {
		//mesh->update();
		GameObject::doStart();

		onUpdate();

		GameObject::doDestroy();
	}

	void Application::drawCB() {
		instance()->render();
	}

	void Application::timerCB(int ms) {
		int thisTime = glutGet(GLUT_ELAPSED_TIME);
		Time::update(thisTime);

		glutTimerFunc(ms, timerCB, ms);
		instance()->update();
		glutPostRedisplay();
	}

	void Application::reshapeCB(int width, int height) {
	}
}