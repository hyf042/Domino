#ifndef __MESH_RENDERER_H__
#define __MESH_RENDERER_H__

#include "../../Domino.h"

namespace Domino {
	using std::shared_ptr;

	class MeshRenderer : public Renderer {
	public:
		MeshRenderer() {}
		MeshRenderer(shared_ptr<Material> material):Renderer(material) {}
		virtual ~MeshRenderer();

		void awake() override;

		void render() override;

	private:
		void setLayout(shared_ptr<Shader> shader);
		void setMatrix(shared_ptr<Shader> shader);

		GLuint vbo;
		GLuint ebo;
	};
}

#endif