#pragma once
#include "Vector.h"

class Ray {
public:
		Ray(){}
		Ray(const Vector3f& A, const Vector3f &B) : orig(A), dir(B) {}
		Vector3f Orig() { return orig; }
		const Vector3f& Orig() const { return orig; }
	    Vector3f Dir() { return dir; }
		const Vector3f& Dir() const { return dir; }
		Vector3f Dest(double t) { return orig + dir * t; }
		const Vector3f Dest(double t) const { return orig + dir * t; }
private:
	Vector3f orig;
	Vector3f dir;
};
