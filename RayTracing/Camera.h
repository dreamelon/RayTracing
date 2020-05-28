#pragma once
#include "Ray.h"

class Camera {
	Vector3f pos;
	Vector3f viewPlane_Orig;
	Vector3f vertical;
	Vector3f horizontal;
public:
	Camera(Vector3f Pos = Vector3f(0, 0, 0), Vector3f ViewPlane_Orig = Vector3f(-2, -1, -1),
		Vector3f Vertical = Vector3f(0, 2, 0),Vector3f Horizontal = Vector3f(4, 0, 0)) :
		pos(Pos), viewPlane_Orig(ViewPlane_Orig), vertical(Vertical), horizontal(Horizontal){}

	Ray GetRay(double u, double v) {
		return Ray(pos, viewPlane_Orig + u * horizontal + v * vertical);
	}
};