#pragma once
#include "Vector.h"
#include "Ray.h"
struct Hit_record {
	double t;
	Vector3f p;
	Vector3f normal;
};

class Object {
public:
	virtual bool intersect(const Ray&, double tmin, double tmax, Hit_record&) const = 0;
};