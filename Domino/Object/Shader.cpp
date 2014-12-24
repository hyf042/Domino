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

	// Geometry shader
	//const GLchar* defaultGeometryShaderSrc = GLSL(
	//	layout(points) in;
	//	layout(points, max_vertices = 128) out;

	//	in vec3 vColor[];
	//	in float vSides[];
	//	out vec3 fColor;

	//	const float PI = 3.1415926;

	//	void main() {
	//		fColor = vColor[0];

	//		int w = int(2 * vSides[0]);
	//		int h = int(vSides[0]);
	//		float hStep = PI / (h - 1);
	//		float wStep = PI * 2 / w;
	//		float radius = 0.4;
	//		float a = 0;
	//		float b = 0;

	//		for (int i = 0; i < h; i++) {
	//			b = 0;
	//			float sina = sin(a);
	//			float cosa = cos(a);
	//			for (int j = 0; j <= w; j++) {
	//				vec4 offset = vec4(radius * sina * cos(b), radius * sina * sin(b), radius * cosa, 0);
	//				gl_Position = gl_in[0].gl_Position + offset;
	//				EmitVertex();

	//				b += wStep;
	//			}
	//			a += hStep;
	//		}

	//		EndPrimitive();
	//	}
	//);
	const GLchar* defaultGeometryShaderSrc = GLSL(
		layout(points) in;
		layout(points, max_vertices = 128) out;

		in vec3 vColor[];
		in float vSides[];
		out vec3 fColor;

		void main() {
			fColor = vColor[0];
			gl_Position = gl_in[0].gl_Position;
			EmitVertex();
			EndPrimitive();
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

	Shader::Shader() {
		init(defaultVertexShaderSrc, defaultGeometryShaderSrc, defaultFragmentShaderSrc);
	}
	Shader::Shader(const GLchar *vertexShaderSrc, const GLchar *geometryShaderSrc, const GLchar *fragmentShaderSrc) {
		init(vertexShaderSrc, geometryShaderSrc, fragmentShaderSrc);
	}

	Shader::~Shader() {
		glDeleteProgram(_shaderProgram);
		glDeleteShader(_fragmentShader);
		glDeleteShader(_vertexShader);
		//glDeleteShader(_geometryShader);
	}

	void Shader::use() {
		glUseProgram(_shaderProgram);
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

	void Shader::init(const GLchar *vertexShaderSrc, const GLchar *geometryShaderSrc, const GLchar *fragmentShaderSrc) {
		// Compile and activate shaders
		_vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSrc);
		//_geometryShader = createShader(GL_GEOMETRY_SHADER, geometryShaderSrc);
		_fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);

		_shaderProgram = glCreateProgram();
		glAttachShader(_shaderProgram, _vertexShader);
		//glAttachShader(_shaderProgram, _geometryShader);
		glAttachShader(_shaderProgram, _fragmentShader);
		glLinkProgram(_shaderProgram);
		glUseProgram(_shaderProgram);
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