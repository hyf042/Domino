#include "Domino/Domino.h"
#include "Test/Movable.h"
#include "Reduction/PolyRed.h"
using namespace std;
using namespace Domino;

const int WIDTH = 800;
const int HEIGHT = 600;

int calculateLevelDetails(int i, int j) {
	int levelToDetails[] = {4, 8, 16};
	int details = Mathf::abs(i) + Mathf::abs(j);
	return levelToDetails[2];
}

void buildScene() {
	auto texture = shared_ptr<Texture>(new Texture("earth.jpg"));
	auto material = shared_ptr<Material>(new Material(texture));

	auto camera = GameObject::createNew();
	camera->addComponent<Camera>();

	auto obj = GameObject::createNew();
	obj->addComponent(MeshFilter::createSphereMesh(calculateLevelDetails(0, 0)));
	//obj->addComponent(MeshFilter::fromSharedMesh(MeshImporter::createFromFBX("mech_bot.FBX")));
	//obj->addComponent(MeshFilter::createSurfaceMesh());
	auto meshRenderer = shared_ptr<MeshRenderer>(new MeshRenderer(material));
	//meshRenderer->setIsWireframe(true);
	obj->addComponent(meshRenderer);
	obj->addComponent<Movable>();
	obj->getTransform()->localPosition = Vector3(0, 0, 5);
	obj->getTransform()->localScale = Vector3(1, 1, 1);
	//obj->getTransform()->localRotation = Vector3(-Mathf::PI / 2, 0, 0);
	obj->getTransform()->localRotation = Vector3(0, 0, 0);
			
	obj->addComponent<PolyRed>();

}

int main(int argc, char **argv)
{
	Domino::Application::instance()->setUp("Experiment", WIDTH, HEIGHT, argc, argv);

	buildScene();

	Domino::Application::instance()->run();
	return 0;
}