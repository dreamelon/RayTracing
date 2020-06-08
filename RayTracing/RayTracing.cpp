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
#include "Tools.h"
#include "Color.h"
#include "Specular.h"
#include "Diffuse.h"
#include "Dielectric.h"
#include <chrono>
const int sample = 10;
const int depth = 50;

inline void UpdateProgress(double progress)
{
	int barWidth = 70;

	std::cout << "[";
	int pos = barWidth * progress;
	for (int i = 0; i < barWidth; ++i) {
		if (i < pos) std::cout << "=";
		else if (i == pos) std::cout << ">";
		else std::cout << " ";
	}
	std::cout << "] " << int(progress * 100.0) << " %\r";
	std::cout.flush();
};

Vector3f color(const Ray& ray, ObjectList& scene, int depth) {
	if (depth <= 0)
		return Vector3f(0);
	Hit_record rec;
	if (scene.Intersect(ray, Epsilon, infinity, rec)) {	
		Ray scattered;
		Color attenuation;
		if (rec.mat_ptr->scatter(ray, rec, attenuation, scattered)) {
			return attenuation * color(scattered, scene, depth - 1);
		}
		return Color(0);
	}

	Vector3f dir = normalize(ray.Dir());
	double t = 0.5f * (dir.y + 1.f);
	return (1.f - t) * Vector3f(1, 1, 1) + t * Vector3f(0.5f, 0.7f, 1.f);
}


int main()
{
	std::fstream fs("result.ppm");
	int width = 400, height = 200;
	Camera camera;

	fs << "P3\n" << width << " " << height << "\n255\n";

	//Object* list[2]{ new Sphere(Vector3f(0, 0, -1), 0.5), new Sphere(Vector3f(0, -100.5, -1), 100) };
	ObjectList scene;
	scene.Add(std::make_shared<Sphere>(Vector3f(0, 0, -1), 0.5, std::make_shared<Diffuse>(Color(0.1, 0.2, 0.5))));
	scene.Add(std::make_shared<Sphere>(Vector3f(0, -100.5, -1), 100, std::make_shared<Diffuse>(Color(0.8, 0.8, 0.0))));
	scene.Add(std::make_shared<Sphere>(Vector3f(1, 0, -1),  0.5, std::make_shared<Specular>(Color(0.8, 0.6, 0.2), 0.3)));
	scene.Add(std::make_shared<Sphere>(Vector3f(-1, 0, -1), 0.5, std::make_shared<Dielectric>(1.5)));
	scene.Add(std::make_shared<Sphere>(Vector3f(-1, 0, -1), -0.45, std::make_shared<Dielectric>(1.5)));

	auto start = std::chrono::system_clock::now();

	for (int j = height - 1; j >= 0; j--) {
		for (int i = 0; i < width; i++) {
			double r = double(i) / (double)width;
			double g = double(j) / double(height);
			Color col;
			for (int s = 0; s < sample; s++) {
				double r = double(i + random_double()) / (double)width;
				double g = double(j + random_double()) / double(height);
				col += color(camera.GetRay(r, g), scene, depth);
			}
			col = col / sample;
			int ir = int(COL_MAX * sqrt(col.x));
			int ig = int(COL_MAX * sqrt(col.y));
			int ib = int(COL_MAX * sqrt(col.z));
			fs << ir << " " << ig << " " << ib << "\n";
		}
		UpdateProgress(double(height - j) / double(height));
	}
	UpdateProgress(1.);
	auto stop = std::chrono::system_clock::now();

	std::cout << "Render complete: \n";
	std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::hours>(stop - start).count() << " hours\n";
	std::cout << "          : " << std::chrono::duration_cast<std::chrono::minutes>(stop - start).count() << " minutes\n";
	std::cout << "          : " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() << " seconds\n";
}
