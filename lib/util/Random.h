#ifndef LIB_UTIL_RANDOM_H
#define LIB_UTIL_RANDOM_H

#include <cstdlib>

namespace Zerg {

float randf() { return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);}
float randf(float start, float end) { return (randf() * (end - start)) + start;}

}

#endif