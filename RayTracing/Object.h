#pragma once
#include "Vector.h"
#include "Ray.h"
class Object {
	virtual bool intersect(const Ray&, float, uint32_t, Vector2f&) const = 0;
};