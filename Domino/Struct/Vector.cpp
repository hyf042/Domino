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

	float Vector3::dotToLineDistant(const Vector3& d, const Vector3& v1, const Vector3& v2) {
		float x1 = d.x, y1 = d.y, z1 = d.z;
		float x2 = v1.x, y2 = v1.y, z2 = v1.z;
		float x3 = v2.x, y3 = v2.y, z3 = v2.z;
		float up = Mathf::sqrt(Mathf::sqr((y2-y1)*(z3-z1)-(z2-z1)*(y3-y1)) +
			Mathf::sqr((z2-z1)*(x3-x1)-(x2-x1)*(z3-z1)) +
			Mathf::sqr((x2-x1)*(y3-y1)-(y2-y1)*(x3-x1)));
		float down = Mathf::sqrt(Mathf::sqr(x3-x2) + Mathf::sqr(y3-y2) + Mathf::sqr(z3-z2));
		return up / down;
	}
}