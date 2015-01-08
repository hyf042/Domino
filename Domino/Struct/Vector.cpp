#include "../Domino.h"

namespace Domino {
	Vector2 operator+(const Vector2 &a, const Vector2 &b) {
		return Vector2(a.x + b.x, a.y + b.y);
	}

	double Vector3::magnitude() const {
		return sqrtf(x * x + y * y + z * z);
	}

	Vector3 Vector3::normalize() const {
		float l = magnitude();
		return Vector3(x / l, y / l, z / l);
	}

	Vector3 operator+(const Vector3 &a, const Vector3 &b) {
		return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
	}
	Vector3 operator-(const Vector3 &a, const Vector3 &b) {
		return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
	}
	Vector3 operator*(const Vector3 &a, const Vector3 &b) {
		return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
	}
	Vector3 operator*(const Vector3 &a, double b) {
		return Vector3(a.x * b, a.y * b, a.z * b);
	}
	Vector3 operator/(const Vector3 &a, double b) {
		return Vector3(a.x / b, a.y / b, a.z / b);
	}
	float Vector3::dot(const Vector3 &a, const Vector3 &b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}
	Vector3 Vector3::cross(const Vector3 &a, const Vector3 &b) {
 		return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
	}
}