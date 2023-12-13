#pragma once
#include <random>

// Random class taken from Project 3 materials. Credit to instructor for approach.
class Random
{
	static std::mt19937 random;
public:
	static int RandomInt(int min, int max);
	static float RandomFloat(float min, float max);
};

