#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "../../Domino.h"

namespace Domino {
	class Mesh;
	class Material;
	class MeshFilter;

	class Renderer : public Component {
	public:
		Renderer(shared_ptr<Material> material):material(material) {}
		virtual ~Renderer() {}

		shared_ptr<Material> getMaterial() {
			return material;
		}
		virtual void setMaterial(shared_ptr<Material> material) {
			this->material = material;
		}

		virtual void render(shared_ptr<MeshFilter> meshFilter) = 0;
	protected:
		shared_ptr<Material> material;
	};
}

#endif