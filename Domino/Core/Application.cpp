#include "Application.h"

namespace Domino {
	void Application::setUp(string title, int width, int height, int argc, char **argv) {
		createContext(title, width, height, argc, argv);

		onInit();
	}

	void Application::run() {
		glutMainLoop();
	}

	void Application::onRender(void) {
		mesh->render();
	}

	void Application::onDestroy() {
		mesh->onDestroy();
	}

	void Application::onInit() {
		mesh = shared_ptr<Mesh>(new Mesh(shared_ptr<Shader>(new Shader())));
		mesh->init();
	}

	void Application::createContext(string title, int width, int height, int argc, char **argv) {
		glutInit(&argc, argv);

		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
		glutInitWindowPosition(50, 25);
		glutInitWindowSize(width, height);

		glutCreateWindow(title.c_str());
		glutDisplayFunc(drawFunc);

		createGlewContext();
	}

	void Application::createGlewContext() {
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		}
	}

	void Application::render() {
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		onRender();

		glFlush();
	}

	void Application::drawFunc() {
		instance()->render();
	}
}