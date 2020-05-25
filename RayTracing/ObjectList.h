#pragma once
#include "Object.h"

class ObjectList {
	Object** list;
	int list_size;
public:
	ObjectList(Object** l, int n) : list(l), list_size(n){}
	bool intersect(const Ray&, float tmin, float tmax, Hit_record&) const;
};