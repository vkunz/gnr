#include <math.h>

//VC++ math.h (and others) do not define M_PI
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//An epsilon value for comparisons
#ifndef EPSILON
#define EPSILON 0.01f
#endif

#include "GNRMathVector2D.h"
#include "GNRMathVector3D.h"
#include "GNRMathVector4D.h"
#include "GNRMathMatrix4x4.h"
#include "GNRMathPlane.h"