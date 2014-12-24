#include "Domino/Domino.h"
using namespace std;

const int WIDTH = 800;
const int HEIGHT = 600;

int main(int argc, char **argv)
{
	Domino::Application::instance()->setUp("Experiment", WIDTH, HEIGHT, argc, argv);
	Domino::Application::instance()->run();
	return 0;
}