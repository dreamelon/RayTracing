#pragma once
#include "Material.h"

inline Vector3f Refract(const Vector3f& ray_in, const Vector3f& normal, double etai_over_etat) {
	//Vector3f refract;
	Vector3f u = etai_over_etat * (ray_in - dotProduct(ray_in, normal) * normal);
	Vector3f v = -sqrt(1 - dotProduct(u, u)) * normal;
	return u + v;
}

inline double Schlick(double cosine, double ref_idx) {
	auto r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0)*pow((1 - cosine), 5);
}

class Dielectric : public Material {
	double ref_idx;



public:
	Dielectric(double ri) : ref_idx(ri) {}

	virtual bool scatter(const Ray& r_in, const Hit_record& rec, Color& attenuation, Ray& scattered) const {
		attenuation = Color(1);
		//根据正反面调整折射率,光从空气到玻璃与从玻璃到空气
		double etai_over_etat = rec.front_face ? 1. / ref_idx : ref_idx;

		Vector3f unit_dir = normalize(r_in.Dir());

		double cos_theta = std::min(dotProduct(-unit_dir, rec.normal), 1.);
		double sin_theta = sqrt(1. - cos_theta * cos_theta);

		if (etai_over_etat * sin_theta > 1.) {
			Vector3f reflect_dir = unit_dir - 2 * dotProduct(rec.normal, unit_dir) * rec.normal;
			scattered = Ray(rec.pos, reflect_dir);
			return true;
		}

		double reflect_prob = Schlick(cos_theta, etai_over_etat);
		if (random_double() < reflect_prob) {
			Vector3f reflect_dir = unit_dir - 2 * dotProduct(rec.normal, unit_dir) * rec.normal;
			scattered = Ray(rec.pos, reflect_dir);
			return true;
		}

		Vector3f refract_dir = Refract(unit_dir, rec.normal, etai_over_etat);
		scattered = Ray(rec.pos, refract_dir);

		return true;
	}
};