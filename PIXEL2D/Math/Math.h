#pragma once
#include "..//Core/ValueTypes.h"
#include "MathTypes.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"
#include "Rectangle.h"

#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

namespace PIXL { namespace math{

	inline int Clamp(int value, int min, int max)
	{
		return value > max ? max : (value < min ? min : value);
	}

	inline Float32 Clamp(float value, float min, float max)
	{
		return value > max ? max : (value < min ? min : value);
	}

	inline Float32 Abs(float value)
	{
		return value < 0.0f ? -value : value;
	}

	/*inline Vector2f Abs(Vector2f value)
	{
		return Vector2f(Abs(value.x), Abs(value.y));
	}*/

	inline Float32 ToRadians(float degrees)
	{
		return (float)(degrees * (M_PI / 180.0f));
	}

} }