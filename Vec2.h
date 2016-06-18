#pragma once
namespace dax {
struct Vec2 {
	Vec2() : x(0.0), y(0.0) {}
	Vec2(const double _x, const double _y) : x(_x), y(_y) {}
	Vec2& operator+=(const Vec2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	Vec2& operator-=(const Vec2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	Vec2& operator/=(const double other)
	{
		x /= other;
		y /= other;
		return *this;
	}
	Vec2& operator*=(const double other)
	{
		x *= other;
		y *= other;
		return *this;
	}
	Vec2 operator+(const Vec2& other) const
	{
		return Vec2(x + other.x, y + other.y);
	}
	Vec2 operator-(const Vec2& other) const
	{
		return Vec2(x - other.x, y - other.y);
	}
	Vec2 operator*(const Vec2& other) const
	{
		return Vec2(x * other.x, y * other.y);
	}
	Vec2 operator/(const Vec2& other) const
	{
		return Vec2(x / other.x, y / other.y);
	}
	Vec2 operator+(const double& other) const
	{
		return Vec2(x + other, y + other);
	}
	Vec2 operator-(const double& other) const
	{
		return Vec2(x - other, y - other);
	}
	Vec2 operator*(const double& other) const
	{
		return Vec2(x * other, y * other);
	}
	Vec2 operator/(const double& other) const
	{
		return Vec2(x / other, y / other);
	}
	Vec2 operator-() const
	{
		return Vec2(-x, -y);
	}
	double x;
	double y;
};
}
