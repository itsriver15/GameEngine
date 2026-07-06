#pragma once
#include "pch.h"
namespace nu {
	struct Vector2
	{
		float x, y;
		Vector2() = default;
		Vector2(float x, float y) : x{ x }, y{ y } {}
		Vector2(float z) : x{ z }, y{ z } {}

		Vector2 operator + (Vector2 v){
			return Vector2(this->x + v.x, this->y + v.y);
		}
	};
}
