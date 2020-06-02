#pragma once
#include "Material.h"
#include "Tools.h"
class Diffuse : public Material {
	Color albedo;
public:
	Diffuse(const Color& col) : albedo(col) {}
	virtual bool scatter(const Ray& in, const Hit_record& rec, Color& attenuation, Ray& scattered) const {
		Vector3f scatter_dir = rec.normal + random_unit_vector();
		scattered = Ray(rec.pos, scatter_dir);
		attenuation = albedo;
		return true;
	}
};