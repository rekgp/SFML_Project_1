#include "PerlinNoise.h"


PerlinNoise::PerlinNoise(const unsigned &seed)
{	
	//random generator setup
	std::mt19937 generator(seed);
	std::uniform_real_distribution<float> distribution;
	auto dice = std::bind(distribution, generator);
	for (unsigned i = 0; i < tableSize; i++) {
		//uniform distribution != uniform circle distribution
		float theta = acos(2 * dice() - 1);
		float phi = 2 * dice() * M_PI;
		//makeing distribution on a critcle be uniform 
		float x = cos(phi) * sin(theta);
		float y = sin(phi) * sin(theta);
		float z = cos(theta);
		gradients[i] = Vec3f(x, y, z);
		permutationTable[i] = i;
	}
	//one more random generator
	std::uniform_int_distribution<unsigned> distributionInt;
	auto diceInt = std::bind(distributionInt, generator);
	//generation of random numbers in a table
	for (unsigned i = 0; i < tableSize; i++) {
		std::swap(permutationTable[i], permutationTable[diceInt() & tableSizeMask]);
	}
	//extending the size of a tble to have a 2d vector on each point
	for (unsigned i = 0; i < tableSize; i++) {
		permutationTable[tableSize + i] = permutationTable[i];
	}
}

PerlinNoise::~PerlinNoise() {};

float PerlinNoise::eval(const Vec3f &pos, Vec3f &deriv) {
	//finding the opening position inside our table
	// usage of bitwise or insted of modulo (that why the table is a multiple of 2)
	int xi0 = ((int)std::floor(pos.x)) & tableSizeMask;
	int yi0 = ((int)std::floor(pos.y)) & tableSizeMask;
	int zi0 = ((int)std::floor(pos.z)) & tableSizeMask;

	// finding the closing position inside table
	int xi1 = (xi0 + 1) & tableSizeMask;
	int yi1 = (yi0 + 1) & tableSizeMask;
	int zi1 = (zi0 + 1) & tableSizeMask;

	// getting the exact position inside a cube
	float tx = pos.x - ((int)std::floor(pos.x));
	float ty = pos.y - ((int)std::floor(pos.y));
	float tz = pos.z - ((int)std::floor(pos.z));

	//interpolation 
	float u = quintic(tx);
	float v = quintic(ty);
	float w = quintic(tz);

	float x0 = tx, x1 = tx - 1;
	float y0 = ty, y1 = ty - 1;
	float z0 = tz, z1 = tz - 1;
	//hashing for more randomness
	float a = gradientDotV(hash(xi0, yi0, zi0), x0, y0, z0);
	float b = gradientDotV(hash(xi1, yi0, zi0), x1, y0, z0);
	float c = gradientDotV(hash(xi0, yi1, zi0), x0, y1, z0);
	float d = gradientDotV(hash(xi1, yi1, zi0), x1, y1, z0);
	float e = gradientDotV(hash(xi0, yi0, zi1), x0, y0, z1);
	float f = gradientDotV(hash(xi1, yi0, zi1), x1, y0, z1);
	float g = gradientDotV(hash(xi0, yi1, zi1), x0, y1, z1);
	float h = gradientDotV(hash(xi1, yi1, zi1), x1, y1, z1);
	//this i really dont understand but someone smart did the math and this is needed cuz we are not using linear interpolation ???
	float du = quinticDeriv(tx);
	float dv = quinticDeriv(ty);
	float dw = quinticDeriv(tz);
	//calculating the values from interpolation
	float k0 = a;
	float k1 = (b - a);
	float k2 = (c - a);
	float k3 = (e - a);
	float k4 = (a + d - b - c);
	float k5 = (a + f - b - e);
	float k6 = (a + g - c - e);
	float k7 = (b + c + e + h - a - d - f - g);
	//getting the 
	deriv.x = du * (k1 + k4 * v + k5 * w + k7 * v * w);
	deriv.y = dv * (k2 + k4 * u + k6 * w + k7 * v * w);
	deriv.z = dw * (k3 + k5 * u + k6 * v + k7 * v * w);

	return k0 + k1 * u + k2 * v + k3 * w + k4 * u * v + k5 * u * w + k6 * v * w + k7 * u * v * w;
}
uint8_t PerlinNoise::hash(const int &x, const int &y, const int &z) const
{
	return permutationTable[permutationTable[permutationTable[x] + y]+ z];
}
float PerlinNoise::gradientDotV(uint8_t perm, float x, float y, float z) const
{
	switch (perm & 15) {
	case  0: return  x + y;
	case  1: return -x + y;
	case  2: return  x - y;
	case  3: return -x - y; 
	case  4: return  x + z;
	case  5: return -x + z;
	case  6: return  x - z;
	case  7: return -x - z; 
	case  8: return  y + z;
	case  9: return -y + z; 
	case 10: return  y - z; 
	case 11: return -y - z; 
	case 12: return  y + x;
	case 13: return -x + y;
	case 14: return -y + z;
	case 15: return -y - z;
	}
}
;

inline float quintic(const float &t)
{
	return t *t *t *(t*(t*6 - 15)+10);
}

inline float quinticDeriv(const float &t)
{
	return 30 * t *t *(t*(t-2)+1);
}
