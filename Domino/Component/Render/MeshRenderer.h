#ifndef __MESH_RENDERER_H__
#define __MESH_RENDERER_H__

#include "../../Domino.h"

namespace Domino {
	using std::shared_ptr;

	class MeshRenderer : public Renderer {
		bool isWireframe;
	public:
		MeshRenderer():isWireframe(false) {}
		MeshRenderer(shared_ptr<Material> material):Renderer(material), isWireframe(false) {}
		virtual ~MeshRenderer();

		void awake() override;

		void render() override;

		bool getIsWireframe() const {
			return isWireframe;
		}
		void setIsWireframe(bool value) {
			isWireframe = value;
		}

	private:
		void setLayout(shared_ptr<Shader> shader);
		void setMatrix(shared_ptr<Shader> shader);

		GLuint vbo;
		GLuint ebo;
	};
}

#endif