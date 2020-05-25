#pragma once
#include "Object.h"

class HitableList : public Object {
	Object** list;
	int list_size;
public:
	HitableList(Object** l, int n) : list(l), list_size(n){}
	virtual bool intersect(const Ray&, float tmin, float tmax, Hit_record&) const;
};