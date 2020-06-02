#pragma once
#include "Object.h"
#include <vector>

class ObjectList {
	std::vector<std::shared_ptr<Object>> objects;

public:
	ObjectList() {}
	ObjectList(std::vector<std::shared_ptr<Object>> objs) : objects(objs){}
	void Add(std::shared_ptr<Object> object) { objects.push_back(object); }
	void Clear() { objects.clear(); }
	bool Intersect(const Ray&, double tmin, double tmax, Hit_record&) const;
};