#if !defined(_MATH_H_INCLUDED_)
#define _MATH_H_INCLUDED_


#if !defined(PI)
 #define PI (3.141592653589793238462643383279)
#endif

#define DEG2RAD(d) ((d) * PI / 180)
#define RAD2DEG(r) ((r) * 180 / PI)

#include "vector2d.h"
#include "rand.h"


#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x < y ? x : y)


namespace System{
namespace Math{

	void ConvertCoordinates( long* x, long* y, bool convert );
	void Initialize();
	
}
}


#endif // _MATH_H_INCLUDED_


