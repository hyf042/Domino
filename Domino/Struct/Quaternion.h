#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Domino.h"

namespace Domino {
	struct Quaternion { 
	public:
		static glm::mat4 euler(Vector3 euler) {
			return glm::mat4_cast(glm::quat(euler));
		}
	};
}

#endif