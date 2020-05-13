// RayTracing.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include "Vector.h"
const float COL_MAX = 255.99;

int main()
{
	std::fstream fs("result.ppm");
	int nx = 200, ny = 100;
	fs << "P3\n" << nx << " " << ny << "\n255\n";

	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			float r = float(i) / (float)nx;
			float g = float(j) / float(ny);
			float b = 0.2f;
			Vector3f(r, g, b);
			int ir = int(COL_MAX * r);
			int ig = int(COL_MAX * g);
			int ib = int(COL_MAX * b);
			fs << ir << " " << ig << " " << ib << "\n";

		}
	}

}
