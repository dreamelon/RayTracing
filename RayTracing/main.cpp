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

using std::make_shared;


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
	double t = 0.5 * (dir.y + 1.);
	return (1. - t) * Vector3f(1, 1, 1) + t * Vector3f(0.5, 0.7, 1.);
}

ObjectList Random_scene() {
	ObjectList world;

	auto ground_material = make_shared<Diffuse>(Color(0.5, 0.5, 0.5));
	world.Add(make_shared<Sphere>(Vector3f(0, -1000, 0), 1000, ground_material));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto choose_mat = random_double();
			Vector3f center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

			if ((center - Vector3f(4, 0.2, 0)).length() > 0.9) {
				std::shared_ptr<Material> sphere_material;

				if (choose_mat < 0.8) {
					// diffuse
					auto albedo = Vector3f(random_double(), random_double(), random_double()) * Vector3f(random_double(), random_double(), random_double());
					sphere_material = make_shared<Diffuse>(albedo);
					world.Add(make_shared<Sphere>(center, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95) {
					// metal
					auto albedo = Vector3f(random_double(0.5, 1), random_double(0.5, 1), random_double(0.5, 1));
					auto fuzz = random_double(0, 0.5);
					sphere_material = make_shared<Specular>(albedo, fuzz);
					world.Add(make_shared<Sphere>(center, 0.2, sphere_material));
				}
				else {
					// glass
					sphere_material = make_shared<Dielectric>(1.5);
					world.Add(make_shared<Sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	auto material1 = make_shared<Dielectric>(1.5);
	world.Add(make_shared<Sphere>(Vector3f(0, 1, 0), 1.0, material1));

	auto material2 = make_shared<Diffuse>(Color(0.4, 0.2, 0.1));
	world.Add(make_shared<Sphere>(Vector3f(-4, 1, 0), 1.0, material2));

	auto material3 = make_shared<Specular>(Color(0.7, 0.6, 0.5), 0.0);
	world.Add(make_shared<Sphere>(Vector3f(4, 1, 0), 1.0, material3));

	return world;
}

int main()
{
	std::fstream fs("result.ppm");
	int width = 384, height = 216;
	double fov = 20;
	double aspect = 16. / 9.;
	double aperture = 2;
	Vector3f cameraPos(3, 3, 2);
	Vector3f lookat(0, 0, -1);
	double focus_dist = (cameraPos - lookat).length();
	Camera camera(fov, aspect, aperture, focus_dist, cameraPos, lookat);

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
