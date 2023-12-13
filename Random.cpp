#include "Random.h"
#include <ctime>

// Random class taken from Project 3 materials. Credit to instructor for approach.
std::mt19937 Random::random(time(0));

int Random::RandomInt(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);

	return distribution(random);
}

float Random::RandomFloat(float min, float max)
{
	std::uniform_real_distribution<float> distribution(min, max);

	return distribution(random);
}
