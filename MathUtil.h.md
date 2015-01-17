````
//
//  Math.h
//  fastdelegate
//
//  Created by Kink on 14-9-18.
//  Copyright (c) 2014年 Kink. All rights reserved.
//

#ifndef _math_util_h_2015_1_17_
#define _math_util_h_2015_1_17_
#ifdef __APPLE__
#include <math.h>
#pragma message "apple platform"
#endif
#include <assert.h>
#include "TypeDef.h"
#ifndef PI
#define PI 3.1415926535897932384626433833
#endif

#define ST_EPSILON (0.00001f)
typedef float Real;


class MathUtil
{
public:
	template<typename T>
	static T sqrt_assert(T t)
	{
		assert(t >= 0.0);
		return sqrt(t);
	}
	
	template <typename T>
	static T acos_assert(const T f)
	{
		assert(f >= -1.0f && f <= 1.0f);
		return acos(f);
	}
	
	template <typename T>
	static T asin_assert(const T f)
	{
		assert(f >= -1.0f && f <= 1.0f);
		return asin(f);
	}
	
	static Real toRadian(Real degree) { return degree * (PI / 180.0f); }
	static Real toDegree(Real radian) { return radian * (180.0f / PI); }
	
	
	inline bool isFinite(const float f)
	{
#ifdef _MSC_VER
		return _finite(f) != 0;
#elif defined __APPLE__
		return isfinite(f);
#elif defined __LINUX__ || defined __UNIX__
		return finitef(f);
#else
# error "isFinite not supported"
#endif
		//return std::isfinite (f);
		//return finite (f);
	}
	
	static inline bool isNan(const float f)
	{
#ifdef _MSC_VER
		return _isnan(f) != 0;
#elif defined __APPLE__
		return isnan(f);
#elif defined __LINUX__ || defined __UNIX__
		return isnanf(f);
#else
# error "isNan not supported"
#endif
	}
	
	static uint32_t log2(uint32_t i)
	{
		uint32_t value = 0;
		while( i >>= 1 ) {
			value++;
		}
		return value;
	}
	
	static float lerp(float f0, float f1, float t)
	{
		const float s = 1.0f - t;
		return f0 * s + f1 * t;
	}
	
	static float square(float f)
	{
		return f * f;
	}
	
	
	static bool equal(const float f0, const float f1, const float epsilon = ST_EPSILON)
	{
		return fabs(f0-f1) <= epsilon;
	}
	
	static bool isZero(const float f, const float epsilon = ST_EPSILON)
	{
		return fabs(f) <= epsilon;
	}
	
	static uint32_t iceil(Real value)
	{
		return (uint32_t)::ceil(value);
	}
	
	static Real ceil(Real value)
	{
		return ::ceil(value);
	}
	
	static uint32_t ifloor(Real value)
	{
		return (uint32_t)::floor(value);
	}
	
	static Real floor(Real value)
	{
		return ::floor(value);
	}
	
	static uint32_t iabs(uint32_t value)
	{
		return value > 0 ? value : -value;
	}
	
	static Real abs(Real value)
	{
		return ::abs(value);
	}
};

#endif /* defined(__math_util_h_) */
````
