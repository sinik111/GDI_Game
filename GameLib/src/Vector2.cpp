#include "Vector2.h"

#include <cmath>

#include "DebugUtility.h"

const Vector2 Vector2::Zero = Vector2(0.0f, 0.0f);
const Vector2 Vector2::One = Vector2(1.0f, 1.0f);

const Vector2 Vector2::Up = Vector2(0.0f, 1.0f);
const Vector2 Vector2::Down = Vector2(0.0f, -1.0f);
const Vector2 Vector2::Right = Vector2(1.0f, 0.0f);
const Vector2 Vector2::Left = Vector2(-1.0f, 0.0f);

Vector2::Vector2()
	: x(0.0f), y(0.0f)
{
}

Vector2::Vector2(float x, float y)
	:x(x), y(y)
{
}

Vector2 Vector2::operator=(const Vector2& other)
{
	return Vector2(this->x = other.x, this->y = other.y);
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(this->x + other.x, this->y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(this->x - other.x, this->y - other.y);
}

Vector2 Vector2::operator*(float scalar) const
{
	return Vector2(this->x * scalar, this->y * scalar);
}

Vector2 Vector2::operator/(float scalar) const
{
	if (scalar == 0.0f)
	{
		DebugLog("Cannot divide by zero- Vector2\n");

		return *this;
	}

	return Vector2(this->x / scalar, this->y / scalar);
}

Vector2 Vector2::operator+=(const Vector2& other)
{
	return Vector2(this->x += other.x, this->y += other.y);
}

Vector2 Vector2::operator-=(const Vector2& other)
{
	return Vector2(this->x -= other.x, this->y -= other.y);
}

Vector2 Vector2::operator*=(float scalar)
{
	return Vector2(this->x *= scalar, this->y *= scalar);
}

Vector2 Vector2::operator/=(float scalar)
{
	if (scalar == 0.0f)
	{
		DebugLog("Cannot divide by zero- Vector2\n");

		return *this;
	}

	return Vector2(this->x /= scalar, this->y /= scalar);
}

float Vector2::SquareLength() const
{
	return this->x * this->x + this->y * this->y;
}

float Vector2::Length() const
{
	return sqrt(SquareLength());
}

Vector2 Vector2::Normalized() const
{
	return *this / Length();
}

Vector2 Vector2::Normalize()
{
	return *this /= Length();
}

float Vector2::SquareLength(const Vector2& v)
{
	return v.x * v.x + v.y * v.y;
}

float Vector2::Length(const Vector2& v)
{
	return sqrt(SquareLength(v));
}

Vector2 Vector2::Normalized(const Vector2& v)
{
	return v / Length(v);
}

Vector2 Vector2::Normalize(Vector2& v)
{
	return v /= Length(v);
}

float Vector2::Dot(const Vector2& v1, const Vector2& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}
