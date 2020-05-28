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
