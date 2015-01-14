#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Domino.h"

namespace Domino {

	MeshRenderer::~MeshRenderer() {
		glDeleteBuffers(1, &ebo);
		glDeleteBuffers(1, &vbo);
	}

	void MeshRenderer::awake() {
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);
	}

	void MeshRenderer::render() {
		if (!getMaterial() || !Camera::getMainCamera()) {
			return;
		}
		auto meshFilter = getGameObject()->getComponent<MeshFilter>();
		if (!meshFilter) {
			return;
		}

		auto mesh = meshFilter->getMesh();
		auto vertices = mesh->getVerticesData();
		if (vertices.size() == 0) {
			return;
		}

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

		auto shader = getMaterial()->getShader();
		shader->use();
		setLayout(shader);
		setMatrix(shader);

		if (isWireframe) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		if (mesh->useIndex()) {
			auto elements = mesh->getElementsData();
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(uint32), &elements[0], GL_STATIC_DRAW);
			glDrawElements(GL_TRIANGLES, elements.size(), GL_UNSIGNED_INT, 0);
		}
		else {
			glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		}
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void MeshRenderer::setLayout(shared_ptr<Shader> shader) {
		GLuint shaderProgram = shader->use();

		// Specify the layout of the vertex data
		GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);

		GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
		glEnableVertexAttribArray(colAttrib);
		glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

		GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
		glEnableVertexAttribArray(texAttrib);
		glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	}

	void MeshRenderer::setMatrix(shared_ptr<Shader> shader) {
		GLuint shaderProgram = shader->use();

		GLint uniModel = glGetUniformLocation(shaderProgram, "model");
        
		glm::mat4 model = getTransform()->getModelMatrix();
        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(getTransform()->getModelMatrix()));

		GLint uniView = glGetUniformLocation(shaderProgram, "view");
		glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(Camera::getMainCamera()->getViewMatrix()));

		GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
		glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(Camera::getMainCamera()->getProjectionMatrix()));
	}
}