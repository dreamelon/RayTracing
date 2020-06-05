#pragma once
#include "Material.h"

class Specular : public Material {
	Color albedo;
	double fuzz;
public :
	Specular(const Color& col, double f) : albedo(col), fuzz(f<1 ? f : 1) {}
	virtual bool scatter(const Ray& in, const Hit_record& rec, Color& attenuation, Ray& scattered) const {
		//Vector3f dir = normalize(in.Dir());
		//Vector3f scatter_dir = dir -   2 * dotProduct(dir, rec.normal) * rec.normal;
		Vector3f scatter_dir = normalize(in.Dir() -   2 * dotProduct(in.Dir(), rec.normal) * rec.normal);
		scattered = Ray(rec.pos,  scatter_dir + fuzz * random_in_unit_sphere()) ;
		attenuation = albedo;
		return dotProduct(scatter_dir, rec.normal) > 0;
	}
};