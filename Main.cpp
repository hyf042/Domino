#include "Domino/Domino.h"
#include "Test/Movable.h"
using namespace std;
using namespace Domino;

const int WIDTH = 800;
const int HEIGHT = 600;

int calculateLevelDetails(int i, int j) {
	int levelToDetails[] = {4, 8, 20};
	int details = Mathf::abs(i) + Mathf::abs(j);
	return levelToDetails[2 - details];
}

void buildScene() {
	auto texture = shared_ptr<Texture>(new Texture("lena.jpg"));
	auto material = shared_ptr<Material>(new Material(texture));

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			auto obj = GameObject::createNew();
			obj->addComponent(MeshFilter::createSphereMesh(calculateLevelDetails(i, j)));
			auto meshRenderer = shared_ptr<MeshRenderer>(new MeshRenderer(material));
			obj->addComponent(meshRenderer);
			obj->addComponent<Movable>();
			obj->getTransform()->localPosition = Vector3(i * 2, j * 2, 5);
			obj->getTransform()->localScale = Vector3(1.5f, 1.5f, 1.5f);
			obj->getTransform()->localRotation = Vector3(0, 0, 0);
		}
	}
}

int main(int argc, char **argv)
{
	Domino::Application::instance()->setUp("Experiment", WIDTH, HEIGHT, argc, argv);

	buildScene();

	Domino::Application::instance()->run();
	return 0;
}