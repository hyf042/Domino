#ifndef __MATHF_H__
#define __MATHF_H__

#include "../Domino.h"

namespace Domino {
	class Mathf {
	public:
		static const float PI;
		static const float EPS;

		template<typename T>
		static T min(T a, T b) {
			return a < b ? a : b;
		}
		template<typename T>
		static T max(T a, T b) {
			return a > b ? a : b;
		}
		template<typename T>
		static T clamp(T v, T a, T b) {
			return min(max(v, a), b);
		}

		static float pow(float f, float p) {
			return powf(f,p);
		}

		static float deg2Rad(float deg) {
			return deg * PI / 180.0f;
		}
		static float rad2Deg(float rad) {
			return rad * 180.0f / PI;
		}

		static float floor(float f) {
			return floorf(f);
		}
		static int floorToInt(float f) {
			return (int)floorf(f);
		}

		static float abs(float f) {
			return fabs(f);
		}

		static int abs(int i) {
			return std::abs(i);
		}

		static float fmod(float x, float y) {
			return fmodf(x, y);
		}

		static float sqrt(float f) {
			return sqrtf(f);
		}

		static float sqr(float f) {
			return pow(f, 2.0f);
		}

		static float sin(float f) {
			return sinf(f);
		}

		static float cos(float f) {
			return cosf(f);
		}

		static float tan(float f) {
			return tanf(f);
		}

		static float atan2(float y, float x) {
			return atan2f(y, x);
		}
	};

}

#endif