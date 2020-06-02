#pragma once
#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <random>
const double Epsilon = 0.0001;
const double PI = 3.1415926;
const double COL_MAX = 255.99;
const double infinity = std::numeric_limits<double>::infinity();

inline double degrees_to_radians(double degrees) {
	return degrees * PI / 180;
}

//随机数
inline double random_double() {
	return rand() / (RAND_MAX + 1.);
}

inline double random_double(double min, double max) {
	// Returns a random real in [min,max).
	return min + (max - min)*random_double();
}

//inline double random_double() {
//	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
//	static std::mt19937 generator;
//	return generator(distribution);
//}

//球内采样
inline Vector3f random_in_unit_sphere() {
	Vector3f p;
	do {
		// rand/RAND_MAX范围[0,1), 映射到[-1,1)
		p = 2.f * Vector3f(random_double(), random_double(), random_double()) - Vector3f(1);
	} while (dotProduct(p, p) > 1.f);

	return p;
}


inline Vector3f random_unit_vector() {
	double z = random_double(-1, 1);
	double theta = random_double(0, 2 * PI);
	double r = sqrt(1 - z * z);

	return Vector3f(r * cos(theta), r * sin(theta), z);
}
//与1等价
inline Vector3f random_unit_vector2() {
	double theta = acos(1 - 2 * random_double(0, 1));
	double phi = random_double(0, 2 * PI);

	return Vector3f(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
}

inline Vector3f random_unit_vector3() {
	double theta = random_double(0, 2 * PI);
	double phi = random_double(0, 2 * PI);

	return Vector3f(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
}

inline Vector3f random_in_hemishpere(const Vector3f& normal) {
	Vector3f in_unit_sphere = random_in_unit_sphere();
	if (dotProduct(in_unit_sphere, normal) > 0.)
		return in_unit_sphere;
	else
		return -in_unit_sphere;
}

