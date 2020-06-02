#pragma once
#include "Ray.h"
#include "Object.h"
#include "Color.h"

class Material {
public :
	virtual bool scatter(const Ray& in, const Hit_record& rec, Color& attenuation, Ray& scattered) const = 0;
};