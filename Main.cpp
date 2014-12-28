#include "Domino/Domino.h"
using namespace std;
using namespace Domino;

const int WIDTH = 800;
const int HEIGHT = 600;

void buildScene() {
	auto texture = shared_ptr<Texture>(new Texture("sample.jpg"));
	auto material = shared_ptr<Material>(new Material(texture));

	auto obj = GameObject::createNew();
	obj->AddComponent(MeshFilter::createSphereMesh());
	auto meshRenderer = shared_ptr<MeshRenderer>(new MeshRenderer(material));
	obj->AddComponent(meshRenderer);
}

int main(int argc, char **argv)
{
	Domino::Application::instance()->setUp("Experiment", WIDTH, HEIGHT, argc, argv);

	buildScene();

	Domino::Application::instance()->run();
	return 0;
}