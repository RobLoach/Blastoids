#include "math.h"

#include <cmath>

namespace System{
	extern int Width;
	extern int Height;
namespace Math{
	

	void Initialize(){
		System::Math::InitRandomNumber();
	}


	void ConvertCoordinates( long* x, long* y, bool convert )
	{
	   int Xmiddle;
	   int Ymiddle;
	   Xmiddle = (int)(System::Width/2); //XRES is the Screen resolution in the x direction
	   Ymiddle = (int)(System::Height/2); //YRES is the Screen resolution in the y direction
	
	   if( convert)
	   {
	      *y = -*y;
	      //*x = *x + Xmiddle;
	      //*y = *y + Ymiddle;
	   }
	   else
	   {
	      //*x = *x - Xmiddle;
	      //*y = *y - Ymiddle;
	      *y = -*y;
	   }
	}
	
}
}


