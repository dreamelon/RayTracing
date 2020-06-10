#pragma once

#include <cmath>
#include <iostream>

class Vector3f
{
public:
	Vector3f()
		: x(0)
		, y(0)
		, z(0)
	{}
	Vector3f(double xx)
		: x(xx)
		, y(xx)
		, z(xx)
	{}
	Vector3f(double xx, double yy, double zz)
		: x(xx)
		, y(yy)
		, z(zz)
	{}
	Vector3f operator*(const double& r) const
	{
		return Vector3f(x * r, y * r, z * r);
	}
	Vector3f operator/(const double& r) const
	{
		return Vector3f(x / r, y / r, z / r);
	}

	Vector3f operator*(const Vector3f& v) const
	{
		return Vector3f(x * v.x, y * v.y, z * v.z);
	}
	Vector3f operator-(const Vector3f& v) const
	{
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}
	Vector3f operator+(const Vector3f& v) const
	{
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}
	Vector3f operator-() const
	{
		return Vector3f(-x, -y, -z);
	}
	Vector3f& operator+=(const Vector3f& v)
	{
		x += v.x, y += v.y, z += v.z;
		return *this;
	}
	double length() const {
		return sqrt(x * x + y * y + z * z);
	}
	friend Vector3f operator*(const double& r, const Vector3f& v)
	{
		return Vector3f(v.x * r, v.y * r, v.z * r);
	}
	friend std::ostream& operator<<(std::ostream& os, const Vector3f& v)
	{
		return os << v.x << ", " << v.y << ", " << v.z;
	}
	double x, y, z;
};

class Vector2f
{
public:
	Vector2f()
		: x(0)
		, y(0)
	{}
	Vector2f(double xx)
		: x(xx)
		, y(xx)
	{}
	Vector2f(double xx, double yy)
		: x(xx)
		, y(yy)
	{}
	Vector2f operator*(const double& r) const
	{
		return Vector2f(x * r, y * r);
	}
	Vector2f operator+(const Vector2f& v) const
	{
		return Vector2f(x + v.x, y + v.y);
	}
	double x, y;
};

inline Vector3f lerp(const Vector3f& a, const Vector3f& b, const double& t)
{
	return a * (1 - t) + b * t;
}

inline Vector3f normalize(const Vector3f& v)
{
	double mag2 = v.x * v.x + v.y * v.y + v.z * v.z;
	if (mag2 > 0)
	{
		double invMag = 1 / sqrt(mag2);
		return Vector3f(v.x * invMag, v.y * invMag, v.z * invMag);
	}

	return v;
}

inline double dotProduct(const Vector3f& a, const Vector3f& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline double dotProduct(const Vector2f& a, const Vector2f& b)
{
	return a.x * b.x + a.y * b.y;
}

inline Vector3f crossProduct(const Vector3f& a, const Vector3f& b)
{
	return Vector3f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
