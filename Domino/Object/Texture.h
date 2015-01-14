#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <SOIL/SOIL.h>
#include "../Domino.h"

namespace Domino {
	using std::string;

	class Texture : public Object {
	public:
		Texture(string filename) {
			// Load texture
			glGenTextures(1, &textureId);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureId);

			unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			SOIL_free_image_data(image);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		~Texture() {
			glDeleteTextures(1, &textureId);
		}

		void use() {
			glBindTexture(GL_TEXTURE_2D, textureId);
		}

		uint32 getWidth() const {
			return width;
		}
		uint32 getHeight() const {
			return height;
		}

		uint32 GetNativeTextureID() const {
			return textureId;
		}
	protected:
		GLuint textureId;
		int32 width;
		int32 height;
	};
}

#endif