#include "../Domino.h"

namespace Domino {
	Material::Material() {
		shader = shared_ptr<Shader>(new Shader());
	}
	Material::Material(shared_ptr<Shader> shader):shader(shader) {}
	Material::Material(shared_ptr<Texture> texture):mainTexture(texture) {
		shader = shared_ptr<Shader>(new Shader());
	}
	Material::Material(shared_ptr<Shader> shader, shared_ptr<Texture> texture)
		:shader(shader), mainTexture(texture) {}
}