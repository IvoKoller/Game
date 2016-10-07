#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <cstring> //in order for memcpy and memset to work under linux
namespace evo {
namespace maths {

	inline float toRadians(float degrees)
	{
		return degrees * (M_PI / 180.0f);
	}

} }
