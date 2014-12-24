#include "Mesh.h"

namespace Domino {
	void Mesh::init() {
		// Create VAO
		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		// Create VBO with point coordinates
		glGenBuffers(1, &_vbo);

		GLfloat points[] = {
		//  Position   Color             Texcoords
        -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right
        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom-left
		};

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

		// Create an element array
		GLuint ebo;
		glGenBuffers(1, &ebo);

		GLuint elements[] = {
			0, 1, 2,
			2, 3, 0
		};

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

		setLayout();
	}

	void Mesh::render() {
		glBindVertexArray(_vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void Mesh::onDestroy() {
		glDeleteBuffers(1, &_ebo);
		glDeleteBuffers(1, &_vbo);
		glDeleteVertexArrays(1, &_vao);
		_shader.reset();
	}

	void Mesh::setLayout() {
		GLuint shaderProgram = _shader->getShaderProgram();
		_shader->use();

		// Specify the layout of the vertex data
		GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);

		GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
		glEnableVertexAttribArray(colAttrib);
		glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
	}
}