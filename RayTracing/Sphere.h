#pragma once
#include "Object.h"
class Sphere : public Object {
	Vector3f center;
	double radius;
	std::shared_ptr<Material> mat_ptr;
public:
	bool Intersect(const Ray&, double tmin, double tmax, Hit_record&) const override;
	Sphere(const Vector3f& v, double r, std::shared_ptr<Material> ptr) : center(v), radius(r), mat_ptr(ptr){}
};