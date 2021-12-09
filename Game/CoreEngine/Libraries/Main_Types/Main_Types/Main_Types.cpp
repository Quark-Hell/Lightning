#pragma once

#include "pch.h" 
#include <time.h>  
#include <cmath>
#include <algorithm> 
#include "Main_Types.h"

class Vector2 {
public:
	float x;
public:
	float y;
#pragma region Operators	

public:
	__declspec(dllexport) void operator+=(const Vector2 value) {
		x += value.x;
		y += value.y;
	}
public:
	__declspec(dllexport) void operator+=(const Vector2* value) {
		x += value->x;
		y += value->y;
	}
public:
	__declspec(dllexport) void operator-=(const Vector2 value) {
		x -= value.x;
		y -= value.y;
	}
public:
	__declspec(dllexport) void operator-=(const Vector2* value) {
		x -= value->x;
		y -= value->y;
	}
public:
	__declspec(dllexport) void operator*=(const Vector2 value) {
		x *= value.x;
		y *= value.y;
	}
public:
	__declspec(dllexport) void operator*=(const Vector2* value) {
		x *= value->x;
		y *= value->y;
	}
public:
	__declspec(dllexport) void operator/=(const Vector2 value) {
		x /= value.x;
		y /= value.y;
	}
public:
	__declspec(dllexport) void operator/=(const Vector2* value) {
		x /= value->x;
		y /= value->y;
	}
public:
	__declspec(dllexport) Vector2 operator+(const Vector2 value) const {
		return Vector2(x + value.x, y + value.y);
	}
public:
	__declspec(dllexport) Vector2 operator+(const Vector2* value) const {
		return Vector2(x + value->x, y + value->y);
	}
public:
	__declspec(dllexport) Vector2 operator-(const Vector2 value) const {
		return Vector2(x - value.x, y - value.y);
	}
public:
	__declspec(dllexport) Vector2 operator-(const Vector2* value) const {
		return Vector2(x - value->x, y - value->y);
	}
public:
	__declspec(dllexport) Vector2 operator*(const Vector2 value) const {
		return Vector2(x * value.x, y * value.y);
	}
public:
	__declspec(dllexport) Vector2 operator*(const Vector2* value) const {
		return Vector2(x * value->x, y * value->y);
	}
public:
	__declspec(dllexport) Vector2 operator/(const Vector2 value) const {
		return Vector2(x / value.x, y / value.y);
	}
public:
	__declspec(dllexport) Vector2 operator/(const Vector2* value) const {
		return Vector2(x / value->x, y / value->y);
	}
public:
	__declspec(dllexport) bool operator!=(const Vector2 value) const {
		if (x != value.x && y != value.y)
		{
			return true;
		}
		return false;
	}
public:
	__declspec(dllexport) bool operator!=(const Vector2* value) const {
		if (x != value->x && y != value->y)
		{
			return true;
		}
		return false;
	}
public:
	__declspec(dllexport) bool operator==(const Vector2 value) const {
		if (x == value.x && y == value.y)
		{
			return true;
		}
		return false;
	}
public:
	__declspec(dllexport) bool operator==(const Vector2* value) const {
		if (x == value->x && y == value->y)
		{
			return true;
		}
		return false;
	}
public:
	__declspec(dllexport) bool operator>(const Vector2 value) const {
		if (x > value.x && y > value.y)
		{
			return true;
		}
		return false;
	}
public:
	__declspec(dllexport) bool operator>(const Vector2* value) const {
		if (x > value->x && y > value->y)
		{
			return true;
		}
		return false;
	}
public:
	__declspec(dllexport) bool operator<(const Vector2 value) const {
		if (x < value.x && y < value.y)
		{
			return true;
		}
		return false;
	}
public:
	__declspec(dllexport) bool operator<(const Vector2* value) const {
		if (x < value->x && y < value->y)
		{
			return true;
		}
		return false;
	}

#pragma endregion

public:
	__declspec(dllexport) void Invert() {
		x = -x;
		y = -y;
	}
public:
	__declspec(dllexport) float Magnitude(Vector2 vec1, Vector2 vec2) {

		return sqrtf(vec1.x * vec2.x + vec1.y * vec2.y);
	}
public:
	__declspec(dllexport) static float SquareMagnitude(Vector2 vec1, Vector2 vec2) {
		return abs(vec1.x * vec2.x + vec1.y * vec2.y);
	}
public:
	/*
	__declspec(dllexport) void Normalize() {
		float magnitude = Magnitude();
		if (magnitude > 0)
		{
			x = x / magnitude;
			y = y / magnitude;
		}
	}
	*/

public:
	__declspec(dllexport) static bool Intersect(Vector2 r0, Vector2 r1, Vector2 a, Vector2 b,Vector2 &intersectPoint)
	{
		// Line AB represented as a1x + b1y = c1
		double a1 = r1.y - r0.y;
		double b1 = r0.x - r1.x;
		double c1 = a1 * (r0.x) + b1 * (r0.y);

		// Line CD represented as a2x + b2y = c2
		double a2 = b.y - a.x;
		double b2 = a.x - b.x;
		double c2 = a2 * (a.x) + b2 * (a.x);

		double determinant = a1 * b2 - a2 * b1;

		if (determinant == 0)
		{
			// The lines are parallel. This is simplified
			return false;
		}
		else
		{
			intersectPoint.x = (b2 * c1 - b1 * c2) / determinant;
			intersectPoint.y = (a1 * c2 - a2 * c1) / determinant;
			Vector2 point1;
			point1.x = r0.x;
			point1.y = r1.y;

			Vector2 point2;
			point2.x = r0.x;
			point2.y = intersectPoint.y;

			float sin1 = SquareMagnitude(point1, r1) / SquareMagnitude(r0,r1);
			float cos1 = SquareMagnitude(r0, point1) / SquareMagnitude(r0,r1);

			float sin2 = SquareMagnitude(point2, r1) / SquareMagnitude(r0, r1);
			float cos2 = SquareMagnitude(r0, point2) / SquareMagnitude(r0, r1);
			if (sin1 == sin2 && cos1 == cos2) {
				return true;
			}
			return false;
		}
	}

	/*
public:
	__declspec(dllexport) Vector2 ComponentProduct(const Vector2 vector) {
		return Vector2(x * vector.x,y * vector.y);
	}
public:
	__declspec(dllexport) void ComponentProductUpdate(const Vector2 vector) {
		x *= vector.x;
		y *= vector.y;
	}
public:
	__declspec(dllexport) float ScalarProduct(const Vector2 vector) {
		return x * vector.x + y * vector.y;
	}
public:
	__declspec(dllexport) Vector2 VectorProduct(const Vector2 vector) {
		return 0;
	}
public:
	__declspec(dllexport) float DotProduct(const Vector2 vector) {
		return (x * vector.x) + (y * vector.y);
	}
public:
	__declspec(dllexport) float CrossProduct() {
		return 0;
	}
	*/
	__declspec(dllexport) Vector2(float x = 0, float y = 0) {
		this->x = x;
		this->y = y;
	}
};

class Mesh {
public:   vector <Vector2> Vertices;
public:   vector <Vector2> Triangles;
public:   vector <Vector2> Edges;

public:
	__declspec(dllexport) bool GenerateEdges() {
		size_t VertCount = Vertices.size();
		Edges.clear();
		for (size_t i = 0; i < VertCount; i++)
		{ 
			for (size_t k = 0; k < 2; k++)
			{
				if (i == VertCount - 1 && k == 1) {
					Edges.push_back(Vertices[0]);
					return true;
				}
				Edges.push_back(Vertices[i + k]);
			}
		}
		return true;
	}
};

static class Time {
public:__declspec(dllexport) static float DeltaTime;
private:__declspec(dllexport) static float OldTime;

public:
	__declspec(dllexport) static float UpdateDeltaTime() {
		DeltaTime = clock() - OldTime;
		OldTime = clock();

		return DeltaTime;
	}
};
float Time::DeltaTime;
float Time::OldTime;