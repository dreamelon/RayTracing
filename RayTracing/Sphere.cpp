#include "pch.h"
#include "Sphere.h"

bool Sphere::Intersect(const Ray& r, double tmin, double tmax, Hit_record& hit_record) const {
	Vector3f oc = r.Orig() - center;
	double a = dotProduct(r.Dir(), r.Dir());
	double b = 2.f * dotProduct(oc, r.Dir());
	double c = dotProduct(oc, oc) - radius * radius;
	double discriminant = b * b - 4 * a * c;
	if (discriminant > 0) {
		double result = (-b - sqrt(discriminant)) / (2 * a);
		if (result < tmax && result > tmin) {
			hit_record.t = result;
			hit_record.pos = r.Dest(result);
			hit_record.mat_ptr = mat_ptr;
			Vector3f outward_normal = (hit_record.pos - center) / radius;
			hit_record.SetFaceNormal(r, outward_normal);
			return true;
		}
		result = (-b + sqrt(discriminant)) / (2 * a);
		if (result < tmax && result > tmin) {
			hit_record.t = result;
			hit_record.pos = r.Dest(result);
			Vector3f outward_normal = (hit_record.pos - center) / radius;
			hit_record.SetFaceNormal(r, outward_normal);
			hit_record.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;
}
