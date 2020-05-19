#pragma once
#include "Vector.h"
#include "Ray.h"
struct Hit_record {
	float t;
	Vector3f p;
	Vector3f normal;
};

class Object {
public:
	virtual bool intersect(const Ray&, float tmin, float tmax, Hit_record&) const = 0;
};