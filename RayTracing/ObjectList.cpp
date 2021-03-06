#include "pch.h"
#include "ObjectList.h"

bool ObjectList::Intersect(const Ray& ray, double tmin, double tmax, Hit_record& rec) const
{
	Hit_record temp_rec;
	bool hit_anything = false;
	double closest_sofar = tmax;
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->Intersect(ray, tmin, closest_sofar, temp_rec)) {
			hit_anything = true;
			closest_sofar = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;
}
