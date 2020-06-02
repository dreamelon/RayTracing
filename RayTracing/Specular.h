#pragma once
#include "Material.h"

class Specular : public Material {
	Color albedo;
public :
	Specular(const Color& col) : albedo(col) {}
	virtual bool scatter(const Ray& in, const Hit_record& rec, Color& attenuation, Ray& scattered) const {
		//Vector3f dir = normalize(in.Dir());
		//Vector3f scatter_dir = dir -   2 * dotProduct(dir, rec.normal) * rec.normal;
		Vector3f scatter_dir = normalize(in.Dir() -   2 * dotProduct(in.Dir(), rec.normal) * rec.normal);
		scattered = Ray(rec.pos, normalize(scatter_dir));
		attenuation = albedo;
		return dotProduct(scattered.Dir(), rec.normal) > 0;
	}
};