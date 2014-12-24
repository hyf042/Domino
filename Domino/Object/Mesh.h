#ifndef __MESH_H__
#define __MESH_H__

#include "../Domino.h"

namespace Domino {
	class Shader;

	class Mesh : public Component {
	public:
		Mesh(shared_ptr<Shader> shader): _shader(shader) {}
		override void init();
		override void render();
		override void onDestroy();

	private:
		void setLayout();
	private:
		GLuint _vbo;
		GLuint _vao;
		GLuint _ebo;
		shared_ptr<Shader> _shader;
	};
}

#endif