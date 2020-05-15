// RayTracing.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include "Vector.h"
#include "Ray.h"
const float COL_MAX = 255.99;

Vector3f color(const Ray& ray) {
	Vector3f dir = normalize(ray.Dir());
	float t = 0.5 * (dir.y + 1);
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
