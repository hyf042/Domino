#ifndef __COLOR_H__
#define __COLOR_H__

#include "Vector.h"

namespace Domino {
	struct Vector3;
	struct Vector4;

	struct Color {
		float a,r,g,b;

		Color(float r=1.0f, float g=1.0f, float b=1.0f, float a=1.0f);
		Color(const Color &c);
		Color(const Vector3 &v);
		Color(const Vector4 &v);
		void setValue(float r, float g, float b) {
			setValue(r, g, b, this->a);
		}
		void setValue(float r, float g, float b, float a) {
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}

		static Color black;
		static Color white;
		static Color clear;
		static Color red;
		static Color blue;
		static Color green;
		static Color yellow;
		static Color cyan;
		static Color magenta;

		float operator[](int index);
		friend Color operator+(const Color &a, const Color &b);
		friend Color operator-(const Color &a, const Color &b);
		friend Color operator*(const Color &a, const Color &b);
		friend Color operator*(const Color &a, float b);
		friend Color operator*(float b, const Color &a);
		friend bool operator==(const Color &a, const Color &b);
		friend bool operator!=(const Color &a, const Color &b);

		Color &clip();
	};
}

#endif