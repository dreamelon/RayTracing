#pragma once
#include "Vector.h"

class Ray {
public:
		Ray(){}
		Ray(const Vector3f& A, const Vector3f &B) : orig(A), dir(B) {}
		Vector3f Orig() { return orig; }
		Vector3f Dir() { return dir; }
		Vector3f Dest(float t) { return orig + dir * t; }
private:
	Vector3f orig;
	Vector3f dir;
};
