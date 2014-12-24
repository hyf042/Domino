#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "../Domino.h"

namespace Domino {
	using std::shared_ptr;

	class Shader;
	class Texture;

	class Material {
	public:
		Material();
		Material(shared_ptr<Shader> shader);
		Material(shared_ptr<Texture> texture);
		Material(shared_ptr<Shader> shader, shared_ptr<Texture> texture);

		shared_ptr<Shader> getShader() {
			return shader;
		}
		shared_ptr<Texture> getMainTexture() {
			return mainTexture;
		}
	protected:
		shared_ptr<Shader> shader;
		shared_ptr<Texture> mainTexture;
	};
}

#endif