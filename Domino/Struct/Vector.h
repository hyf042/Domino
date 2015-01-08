#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Domino.h"

namespace Domino {
	struct Vector2;
	struct Vector3;
	struct Vector4;

	struct Vector2 {
		float x, y;
		Vector2():x(0), y(0) {}
		Vector2(float x, float y):x(x), y(y) {}
		friend Vector2 operator+(const Vector2 &a, const Vector2 &b);

		void setValue(float x, float y) {
			this->x = x;
			this->y = y;
		}
	};

	struct Vector3 {
		float x, y, z;
		Vector3():x(0), y(0), z(0) {}
		Vector3(float x, float y, float z):x(x), y(y), z(z) {}

		double magnitude() const;
		Vector3 normalize() const;

		friend Vector3 operator+(const Vector3 &a, const Vector3 &b);
		friend Vector3 operator-(const Vector3 &a, const Vector3 &b);
		friend Vector3 operator*(const Vector3 &a, const Vector3 &b);
		friend Vector3 operator*(const Vector3 &a, double b);
		friend Vector3 operator/(const Vector3 &a, double b);
		static float dot(const Vector3 &a, const Vector3 &b);
		static Vector3 cross(const Vector3 &a, const Vector3 &b) ;
		// Calculate the distant between d and the line consist by v1 and v2
		static float dotToLineDistant(const Vector3& d, const Vector3& v1, const Vector3& v2);

		void setValue(float x, float y, float z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}

		operator glm::vec3() const {
			return glm::vec3(x, y, z);
		}
		Vector3(const glm::vec3 &val) {
			x = val.x;
			y = val.y;
			z = val.z;
		}
	};

	struct Vector4 {
	public:
		float x, y, z, w;
		Vector4():x(0), y(0), z(0), w(0) {}
		Vector4(float x, float y, float z, float w):x(x), y(y), z(z), w(w) {}
		void setValue(float x, float y, float z, float w) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}
	};
}

#endif