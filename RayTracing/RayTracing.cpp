// RayTracing.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include "Vector.h"
#include "Ray.h"

const float COL_MAX = 255.99f;

float HitSphere(const Ray& r, const Vector3f& center, float radius) {
	Vector3f oc = r.Orig() - center;
	float a = dotProduct(r.Dir(), r.Dir());
	float b = 2.f * dotProduct(oc, r.Dir());
	float c = dotProduct(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return -1.f;
	else return (-b - sqrt(discriminant)) / (2.f * a);
}

Vector3f color(const Ray& ray) {
	float t = HitSphere(ray, Vector3f(0, 0, -1), 0.5);
	if (t > 0.f) {
		Vector3f n = normalize(ray.Dest(t) - Vector3f(0, 0, -1));
		return 0.5 * Vector3f(n.x + 1, n.y + 1, n.z + 1);
	}

	Vector3f dir = normalize(ray.Dir());
	t = 0.5f * (dir.y + 1.f);
	return (1.f - t) * Vector3f(1, 1, 1) + t * Vector3f(0.5f, 0.7f, 1.f);
}


int main()
{
	std::fstream fs("result.ppm");
	int nx = 200, ny = 100;
	Vector3f eye(0, 0, 0);
	Vector3f startPoint(-2, -1, -1);
	Vector3f u(4, 0, 0);
	Vector3f v(0, 2, 0);

	fs << "P3\n" << nx << " " << ny << "\n255\n";

	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			float r = float(i) / (float)nx;
			float g = float(j) / float(ny);

			Vector3f col = color(Ray(eye, startPoint + u * r + v * g));
			int ir = int(COL_MAX * col.x);
			int ig = int(COL_MAX * col.y);
			int ib = int(COL_MAX * col.z);
			fs << ir << " " << ig << " " << ib << "\n";

		}
	}

}
