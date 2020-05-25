// RayTracing.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include "Vector.h"
#include "Ray.h"
#include "ObjectList.h"
#include "Sphere.h"
#include "Camera.h"
const float COL_MAX = 255.99f;

//float HitSphere(const Ray& r, const Vector3f& center, float radius) {
//	Vector3f oc = r.Orig() - center;
//	float a = dotProduct(r.Dir(), r.Dir());
//	float b = 2.f * dotProduct(oc, r.Dir());
//	float c = dotProduct(oc, oc) - radius * radius;
//	float discriminant = b * b - 4 * a * c;
//	if (discriminant < 0)
//		return -1.f;
//	else return (-b - sqrt(discriminant)) / (2.f * a);
//}

Vector3f color(const Ray& ray, ObjectList* scene) {
	Hit_record rec;
	if (scene->intersect(ray, 0.f, 100000.F, rec) > 0.f) {
		
		return 0.5 * Vector3f(rec.normal.x + 1, rec.normal.y + 1, rec.normal.z + 1);
	}

	Vector3f dir = normalize(ray.Dir());
	float t = 0.5f * (dir.y + 1.f);
	return (1.f - t) * Vector3f(1, 1, 1) + t * Vector3f(0.5f, 0.7f, 1.f);
}


int main()
{
	std::fstream fs("result.ppm");
	int nx = 200, ny = 100;
	int ns = 100;
	Camera camera;

	fs << "P3\n" << nx << " " << ny << "\n255\n";
	Object* list[2]{ new Sphere(Vector3f(0, 0, -1), 0.5), new Sphere(Vector3f(0, -100.5, -1), 100) };
	ObjectList* scene = new ObjectList(list, 2);
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			float r = float(i) / (float)nx;
			float g = float(j) / float(ny);
			Vector3f col;
			for (int s = 0; s < ns; s++) {
				float r = float(i + rand() / float(RAND_MAX)) / (float)nx;
				float g = float(j + rand() / float(RAND_MAX)) / float(ny);
				col += color(camera.GetRay(r, g), scene);
			}
			col = col / ns;
			int ir = int(COL_MAX * col.x);
			int ig = int(COL_MAX * col.y);
			int ib = int(COL_MAX * col.z);
			fs << ir << " " << ig << " " << ib << "\n";

		}
	}

}
