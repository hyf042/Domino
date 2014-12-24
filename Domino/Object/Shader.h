#ifndef __SHADER_H__
#define __SHADER_H__

#include "../Domino.h"

namespace Domino {
	class Shader {
	public:
		Shader();
		Shader(const GLchar *vertexShaderSrc, const GLchar *fragmentShaderSrc, const GLchar *geometryShaderSrc = NULL);

		~Shader();

		GLuint use();
		GLuint getShaderProgram() const { 
			return shaderProgram; 
		}
		static GLuint createShader(GLenum type, const GLchar* src);
	private:
		void init(const GLchar *vertexShaderSrc, const GLchar *geometryShaderSrc, const GLchar *fragmentShaderSrc = NULL);

		static void outputErrorLog(GLuint shader);
	private:
		GLuint shaderProgram;
		GLuint fragmentShader;
		GLuint vertexShader;
		GLuint geometryShader;
	};
}

#endif