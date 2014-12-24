#ifndef __MESH_RENDERER_H__
#define __MESH_RENDERER_H__

#include "../../Domino.h"

namespace Domino {
	using std::shared_ptr;

	class Shader;
	class Mesh;
	class MeshFilter;

	class MeshRenderer : public Renderer {
	public:
		MeshRenderer(shared_ptr<Material> material):Renderer(material) {}
		virtual ~MeshRenderer();

		void init() override;

		void setMaterial(shared_ptr<Material> material) override;

		void render(shared_ptr<MeshFilter> meshFilter) override;

	private:
		void setLayout(shared_ptr<Shader> shader);
		void setMatrix(shared_ptr<Shader> shader);

		GLuint vbo;
		GLuint ebo;
	};
}

#endif