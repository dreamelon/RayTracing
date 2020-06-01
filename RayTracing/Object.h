#pragma once
#include "Vector.h"
#include "Ray.h"

class Material;

struct Hit_record {
	double t;
	Vector3f pos;
	Vector3f normal;
	std::shared_ptr<Material> mat_ptr;
	bool front_face;

	void SetFaceNormal(const Ray& r, const Vector3f outwardNormal) {
		front_face = dotProduct(r.Dir(), outwardNormal) < 0;
		normal = front_face ? outwardNormal : -outwardNormal;
	}
};

class Object {
public:
	virtual bool intersect(const Ray&, double tmin, double tmax, Hit_record&) const = 0;
};