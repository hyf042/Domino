#ifndef __VECTOR_H__
#define __VECTOR_H__

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
	};

	struct Vector3 {
		float x, y, z;
		Vector3():x(0), y(0), z(0) {}
		Vector3(float x, float y, float z):x(x), y(y), z(z) {}

		double magnitude() const;
		Vector3 normalize() const;

		friend Vector3 operator+(const Vector3 &a, const Vector3 &b);
		friend Vector3 operator-(const Vector3 &a, const Vector3 &b);
		friend Vector3 operator*(const Vector3 &a, double b);
		friend Vector3 operator/(const Vector3 &a, double b);
		static float dot(const Vector3 &a, const Vector3 &b);
		static Vector3 cross(const Vector3 &a, const Vector3 &b) ;
	};

	struct Vector4 {
	public:
		float x, y, z, w;
		Vector4():x(0), y(0), z(0), w(0) {}
		Vector4(float x, float y, float z, float w):x(x), y(y), z(z), w(w) {}
	};
}

#endif