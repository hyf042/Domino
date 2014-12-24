#ifndef __SHADER_H__
#define __SHADER_H__

#include "../Domino.h"

namespace Domino {
	class Shader {
	public:
		Shader();
		Shader(const GLchar *vertexShaderSrc, const GLchar *geometryShaderSrc, const GLchar *fragmentShaderSrc);

		~Shader();

		void use();
		GLuint getShaderProgram() const { 
			return _shaderProgram; 
		}
		static GLuint createShader(GLenum type, const GLchar* src);
	private:
		void init(const GLchar *vertexShaderSrc, const GLchar *geometryShaderSrc, const GLchar *fragmentShaderSrc);

		static void outputErrorLog(GLuint shader);
	private:
		GLuint _shaderProgram;
		GLuint _fragmentShader;
		GLuint _vertexShader;
		GLuint _geometryShader;
	};
}

#endif