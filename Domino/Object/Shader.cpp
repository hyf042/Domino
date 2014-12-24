#include "Shader.h"

namespace Domino {
	using std::string;

	// Shader macro
	#define GLSL(src) "#version 150 core\n" #src

	// Vertex shader
	const GLchar* defaultVertexShaderSrc = GLSL(
		in vec2 pos;
		in vec3 color;
		out vec3 Color;

		void main() {
			Color = color;
			gl_Position = vec4(pos, 0.0, 1.0);
		}
	);

	// Fragment shader
	const GLchar* defaultFragmentShaderSrc = GLSL(
		in vec3 Color;
		out vec4 outColor;

		void main() {
			outColor = vec4(Color, 1.0);
		}
	);

	// Shader sources
	const GLchar* vertexSource =
		"#version 150 core\n"
		"in vec3 position;"
		"in vec3 color;"
		"in vec2 texcoord;"
		"out vec3 Color;"
		"out vec2 Texcoord;"
		"uniform mat4 model;"
		"uniform mat4 view;"
		"uniform mat4 proj;"
		"void main() {"
		"   Color = color;"
		"   Texcoord = texcoord;"
		"   gl_Position = proj * view * model * vec4(position, 1.0);"
		"}";
	const GLchar* fragmentSource =
		"#version 150 core\n"
		"in vec3 Color;"
		"in vec2 Texcoord;"
		"out vec4 outColor;"
		"uniform sampler2D tex;"
		"void main() {"
		"   outColor = texture(tex, Texcoord) * vec4(Color, 1.0);"
		"}";

	Shader::Shader() {
		init(vertexSource, fragmentSource);
	}
	Shader::Shader(const GLchar *vertexShaderSrc, const GLchar *fragmentShaderSrc, const GLchar *geometryShaderSrc) {
		init(vertexShaderSrc, fragmentShaderSrc, geometryShaderSrc);
	}

	Shader::~Shader() {
		glDeleteProgram(shaderProgram);
		glDeleteShader(fragmentShader);
		glDeleteShader(vertexShader);
		//glDeleteShader(_geometryShader);
	}

	GLuint Shader::use() {
		glUseProgram(shaderProgram);
		return shaderProgram;
	}

	// Shader creation helper
	GLuint Shader::createShader(GLenum type, const GLchar* src) {
		GLuint shader = glCreateShader(type);
		glShaderSource(shader, 1, &src, nullptr);
		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if(isCompiled == GL_FALSE)
		{
			outputErrorLog(shader);
			glDeleteShader(shader); // Don't leak the shader.
		}
		return shader;
	}

	void Shader::init(const GLchar *vertexShaderSrc, const GLchar *fragmentShaderSrc, const GLchar *geometryShaderSrc) {
		// Compile and activate shaders
		vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSrc);
		fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);
		if (geometryShaderSrc != NULL) {
			geometryShader = createShader(GL_GEOMETRY_SHADER, geometryShaderSrc);
		}

		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		if (geometryShaderSrc != NULL) {
			glAttachShader(shaderProgram, geometryShader);
		}
		glLinkProgram(shaderProgram);
		glUseProgram(shaderProgram);
	}

	void Shader::outputErrorLog(GLuint shader) {
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
 
		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
		string output = "";
		for (auto c : errorLog) {
			output += c;
		}
		Debug::log(output);
	}
}