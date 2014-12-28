#include "../Domino.h"

namespace Domino {
	Color::Color(float r, float g, float b, float a){
		this->r = r;this->g=g;this->b=b;this->a=a;
	}
	Color::Color(const Color &c){
		r=c.r;g=c.g;b=c.b;a=c.a;
	}
	Color::Color(const Vector3 &v){
		r=v.x;g=v.y;b=v.z;a=1;
	}
	Color::Color(const Vector4 &v){
		r=v.x;g=v.y;b=v.z;a=v.w;
	}

	Color Color::black(0,0,0);
	Color Color::white(1,1,1);
	Color Color::clear(0,0,0,0);
	Color Color::red(1,0,0);
	Color Color::green(0,1,0);
	Color Color::blue(0,0,1);
	Color Color::yellow(1,1,0);
	Color Color::cyan(0,1,1);
	Color Color::magenta(1,0,1);
	

	Color operator+(const Color &a, const Color &b){
		return Color(a.r+b.r, a.g+b.g, a.b+b.b, a.a+b.a).clip();
	}
	Color operator-(const Color &a, const Color &b){
		return Color(a.r-b.r, a.g-b.g, a.b-b.b, a.a-b.a).clip();
	}
	Color operator*(const Color &a, const Color &b){
		return Color(a.r*b.r, a.g*b.g, a.b*b.b, a.a*b.a).clip();
	}
	Color operator*(const Color &a, float b){
		return Color(a.r*b, a.g*b, a.b*b, a.a*b).clip();
	}
	Color operator*(float b, const Color &a){
		return Color(a.r*b, a.g*b, a.b*b, a.a*b).clip();
	}
	bool operator==(const Color &a, const Color &b){
		return Mathf::abs(a.r-b.r)<Mathf::EPS
				&& Mathf::abs(a.g-b.g)<Mathf::EPS
				&& Mathf::abs(a.b-b.b)<Mathf::EPS
				&& Mathf::abs(a.a-b.a)<Mathf::EPS;

	}
	bool operator!=(const Color &a, const Color &b){
		return !(a==b);
	}

	Color &Color::clip(){
		a = Mathf::clamp(a,0.f,1.f);
		r = Mathf::clamp(r,0.f,1.f);
		g = Mathf::clamp(g,0.f,1.f);
		b = Mathf::clamp(b,0.f,1.f);
		return *this;
	}
}