#pragma once
#include "Material.h"

class Dielectric : public Material {
	double ref_idx;

	Vector3f Refract(const Vector3f& ray_in, const Vector3f& normal, double etai_over_etat) const {
		//Vector3f refract;
		Vector3f u = etai_over_etat * (ray_in - dotProduct(ray_in, normal) * normal);
		Vector3f v = -sqrt(1 - dotProduct(u, u)) * normal;
		return u + v;
	}
public:
	Dielectric(double ri) : ref_idx(ri) {}

	virtual bool scatter(const Ray& r_in, const Hit_record& rec, Color& attenuation, Ray& scattered) const {
		attenuation = Color(1);
		double etai_over_etat;
		//根据正反面调整折射率
		if (rec.front_face) {
			etai_over_etat = 1. / ref_idx;
		}
		else {
			etai_over_etat = ref_idx;
		}

		Vector3f unit_dir = normalize(r_in.Dir());
		Vector3f refract_dir = Refract(r_in.Dir(), rec.normal, etai_over_etat);

		return true;
	}
};