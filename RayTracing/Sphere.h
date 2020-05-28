#pragma once
#include "Object.h"
class Sphere : public Object {
	Vector3f center;
	double radius;
public:
	bool intersect(const Ray&, double tmin, double tmax, Hit_record&) const override;
	Sphere(const Vector3f& v = Vector3f(0,0,0), double r = 1.) : center(v), radius(r){}
};