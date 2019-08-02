#include "stdafx.h"
#include "Utility.h"
#include <chrono>

// seeding random number generator
std::default_random_engine engine{static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count())};


// get a random number generator using the stl uniform distribution function
int getRandomNumber(int max) 
{
    std::uniform_int_distribution<int> int_distribution(max);
    return int_distribution(engine);
}

// get a random number generator using the stl uniform distribution function
int getRandomNumber(int min, int max) 
{
    std::uniform_int_distribution<int> int_distribution(min, max);
    return int_distribution(engine);
}
