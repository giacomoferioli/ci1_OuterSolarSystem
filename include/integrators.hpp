#include "math.h"
#include "Common.hpp"

#ifndef INTEGRATORS
#define INTEGRATORS

void calcYprime();
void euler_expl(double h, int steps=1);
void euler_si(double h,int steps=1);

#endif