#pragma once
#include "Ray.h"
#include "Tools.h"
class Camera {
	Vector3f pos;
	Vector3f viewPlane_Orig;
	Vector3f vertical;
	Vector3f horizontal;
public:
	Camera(double fov, double aspect, Vector3f Pos = Vector3f(0, 0, 0), Vector3f LookAt = Vector3f(0, 0, -1),   Vector3f Up = Vector3f(0,1,0))
		{
		double theta = degrees_to_radians(fov / 2);
		double height = 2 * tan(theta);
		double width = height * aspect;

		Vector3f w = normalize(pos - LookAt);
		Vector3f u = normalize(crossProduct(Up, w));
		Vector3f v = crossProduct(w, u);

		pos = Pos;
		horizontal = u * width;
		vertical = v * height;
		viewPlane_Orig = pos - horizontal / 2 - vertical / 2 - w;
	
	}

	Ray GetRay(double u, double v) {
		return Ray(pos, viewPlane_Orig + u * horizontal + v * vertical - pos) ;
	}
};