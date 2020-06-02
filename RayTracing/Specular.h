#pragma once
#include "Material.h"

class Specular : public Material {
	Color albedo;
public :
	Specular(const Color& col) : albedo(col) {}
	virtual bool scatter(const Ray& in, const Hit_record& rec, Color& attenuation, Ray& scattered) {
		Vector3f scatter_dir = in.Dir - 2 * dotProduct(in.Dir, rec.normal) * in.Dir;
		scattered = Ray(rec.pos, scatter_dir);
		attenuation = albedo;
		return dotProduct(scattered.Dir(), rec.normal) > 0;
	}
};