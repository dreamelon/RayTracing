#pragma once
#include "Object.h"
class Sphere : public Object {
	Vector3f center;
	float radius;
public:
	bool intersect(const Ray&, float tmin, float tmax, Hit_record&) const override;
	Sphere(const Vector3f& v = Vector3f(0,0,0), float r = 1.f) : center(v), radius(r){}
};