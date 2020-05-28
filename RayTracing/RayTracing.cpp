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
#include <stdlib.h>

const float COL_MAX = 255.99f;
const int sample = 50;
const int depth = 50;
const float Epsilon = 0.0001f;

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

Vector3f random_in_unit_sphere() {
	Vector3f p;
	do {
		// rand/RAND_MAX范围[0,1), 映射到[-1,1)
		p = 2.f * Vector3f(rand()/ float(RAND_MAX), rand()/ float(RAND_MAX), rand()/ float(RAND_MAX)) - Vector3f(1, 1, 1);
	} while (dotProduct(p,p) > 1.f);

	return p;
}

Vector3f random_in_unit_sphere() {
	Vector3f p;
	do {
		// rand/RAND_MAX范围[0,1), 映射到[-1,1)
		p = 2.f * Vector3f(rand() / float(RAND_MAX), rand() / float(RAND_MAX), rand() / float(RAND_MAX)) - Vector3f(1, 1, 1);
	} while (dotProduct(p, p) > 1.f);

	return p;
}
Vector3f color(const Ray& ray, ObjectList* scene, int depth) {
	if (depth <= 0)
		return Vector3f(0);
	Hit_record rec;
	if (scene->intersect(ray, Epsilon, std::numeric_limits<float>::max(), rec) > 0.f) {	
		//以p+n为圆心，单位圆内随机取点target， target-p为新的光线方向，p为起点， 模拟diffuse
		Vector3f target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5 * color(Ray(rec.p, target - rec.p), scene, depth - 1);
	}

	Vector3f dir = normalize(ray.Dir());
	float t = 0.5f * (dir.y + 1.f);
	return (1.f - t) * Vector3f(1, 1, 1) + t * Vector3f(0.5f, 0.7f, 1.f);
}


int main()
{
	std::fstream fs("result.ppm");
	int nx = 400, ny = 200;
	Camera camera;

	fs << "P3\n" << nx << " " << ny << "\n255\n";
	Object* list[2]{ new Sphere(Vector3f(0, 0, -1), 0.5), new Sphere(Vector3f(0, -100.5, -1), 100) };
	ObjectList* scene = new ObjectList(list, 2);
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			float r = float(i) / (float)nx;
			float g = float(j) / float(ny);
			Vector3f col;
			for (int s = 0; s < sample; s++) {
				float r = float(i + rand() / float(RAND_MAX)) / (float)nx;
				float g = float(j + rand() / float(RAND_MAX)) / float(ny);
				col += color(camera.GetRay(r, g), scene, depth);
			}
			col = col / sample;
			int ir = int(COL_MAX * sqrt(col.x));
			int ig = int(COL_MAX * sqrt(col.y));
			int ib = int(COL_MAX * sqrt(col.z));
			fs << ir << " " << ig << " " << ib << "\n";

		}
	}

}
