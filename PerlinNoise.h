#pragma once
#define _USE_MATH_DEFINES
#include "Vec3.h"
#include <random>
#include <functional>
#include <cmath>

class PerlinNoise
{
public:
	PerlinNoise(const unsigned &seed = 2022);
	virtual ~PerlinNoise();

	float eval(const Vec3f &pos, Vec3f &deriv);

private:
	uint8_t hash(const int &x, const int &y, const int &z)const;
	float gradientDotV(uint8_t perm, float x, float y, float z) const;

	static const unsigned tableSize = 256;
	static const unsigned tableSizeMask = tableSize - 1;
	Vec3f gradients[tableSize];
	unsigned permutationTable[tableSize * 2];
};

inline
float quintic(const float &t);

inline 
float quinticDeriv(const float &t);

