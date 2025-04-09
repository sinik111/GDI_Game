#pragma once

struct Vector2
{
public:
	float x;
	float y;

public:
	Vector2();
	Vector2(float x, float y);

public:
	Vector2& operator=(const Vector2& other);

	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator*(float scalar) const;
	Vector2 operator/(float scalar) const;

	Vector2& operator+=(const Vector2& other);
	Vector2& operator-=(const Vector2& other);
	Vector2& operator*=(float scalar);
	Vector2& operator/=(float scalar);

public:
	float SquareLength() const;
	float Length() const;
	Vector2 Normalized() const;
	void Normalize();

public:
	static float Dot(const Vector2& v1, const Vector2& v2);

public:
	static const Vector2 Zero;
	static const Vector2 One;

	static const Vector2 Up;
	static const Vector2 Down;
	static const Vector2 Right;
	static const Vector2 Left;
};