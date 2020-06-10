#pragma once
#include "Ray.h"
#include "Tools.h"

inline Vector2f Random_in_unitdisk() {
	while (true) {
		auto p = Vector2f(random_double(-1, 1), random_double(-1, 1));
		if (dotProduct(p, p) >= 1)
			continue;
		return p;
	}
}

class Camera {
	Vector3f pos;
	Vector3f viewPlane_Orig;
	Vector3f vertical;
	Vector3f horizontal;
	Vector3f u, v, w;
	double lens_radius;
public:
	Camera(double fov, double aspect, double aperture, double focus_dist, Vector3f Pos = Vector3f(0, 0, 0), Vector3f LookAt = Vector3f(0, 0, -1), Vector3f Up = Vector3f(0, 1, 0))
	{
		//焦距focus_dist


		double theta = degrees_to_radians(fov / 2);
		//单位成像平面, z = -1;
		double height = 2 * tan(theta);
		double width = height * aspect;

		Vector3f w = normalize(pos - LookAt);
		Vector3f u = normalize(crossProduct(Up, w));
		Vector3f v = crossProduct(w, u);

		pos = Pos;
		horizontal = focus_dist * u * width;
		vertical = focus_dist * v * height;
		viewPlane_Orig = pos - horizontal / 2 - vertical / 2 - focus_dist * w;

		lens_radius = aperture / 2;
	}


	Ray GetRay(double s, double t) const {
		Vector2f rd = Random_in_unitdisk() * lens_radius;
		//相机原点，要根据相机坐标系偏移，不能直接用
		Vector3f offset = u * rd.x + v * rd.y;
		return Ray(pos + offset, viewPlane_Orig + s * horizontal + t * vertical - pos - offset);
	}
};