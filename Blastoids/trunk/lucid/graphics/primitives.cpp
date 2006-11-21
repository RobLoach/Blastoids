#include <SDL/SDL.h>
#include "SDL_gfx/SDL_gfxPrimitives.h"

#include "primitives.h"

 

namespace System{

namespace Graphics{
 

	Uint32 MakeColour(int r, int g, int b, int a){
		if(System::Screen != NULL)
			return SDL_MapRGBA(System::Screen->format, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a);
		else
			return 0;
	}

	Uint32 MakeColour(int r, int g, int b){
		if(System::Screen != NULL)
			return SDL_MapRGB(System::Screen->format, (Uint8)r, (Uint8)g, (Uint8)b);
		else
			return 0;
	}

	int DrawPixel(int x, int y, Uint32 color){
		return pixelColor(System::Screen, (Sint16)x - CameraX, (Sint16)y - CameraY, color);
	}
	int DrawPixel(int x, int y, int r, int g, int b, int a){
		return pixelRGBA(System::Screen, (Sint16)x - CameraX, (Sint16)y - CameraY, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a);
	}
	
	int DrawHorizontalLine(int x1, int x2, int y, Uint32 color){
		return hlineColor(System::Screen, (Sint16)x1 - CameraX, (Sint16)x2 - CameraX, (Sint16)y - CameraY, color);
	}
	int DrawHorizontalLine(int x1, int x2, int y, int r, int g, int b, int a){
		return hlineRGBA(System::Screen, (Sint16)x1 - CameraX, (Sint16)x2 - CameraX, (Sint16)y - CameraY, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a);
	}
	
	int DrawVerticalLine(int x, int y1, int y2, Uint32 color){
		return vlineColor(System::Screen, (Sint16)x - CameraX, (Sint16)y1 - CameraY, (Sint16)y2 - CameraY, color);
	}
	int DrawVerticalLine(int x, int y1, int y2, int r, int g, int b, int a){
		return vlineRGBA(System::Screen, (Sint16)x - CameraX, (Sint16)y1 - CameraY, (Sint16)y2 - CameraY, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a);
	}
	
	int DrawRectangle(int x1, int y1, int x2, int y2, Uint32 color){
		return rectangleColor(System::Screen, (Sint16)x1 - CameraX, (Sint16)y1 - CameraY, (Sint16)x2 - CameraX, (Sint16)y2 - CameraY, color);
	}
	int DrawRectangle(int x1, int y1, int x2, int y2, int r, int g, int b, int a){
		return rectangleRGBA(System::Screen, (Sint16)x1 - CameraX, (Sint16)y1 - CameraY, (Sint16)x2 - CameraX, (Sint16)y2 - CameraY, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a);
	}
	
	int DrawFilledRectangle(int x1, int y1, int x2, int y2, Uint32 color){
		return boxColor(System::Screen, (Sint16)x1 - CameraX, (Sint16)y1 - CameraY, (Sint16)x2 - CameraX, (Sint16)y2 - CameraY, color);
	}
	int DrawFilledRectangle(int x1, int y1, int x2, int y2, int r, int g, int b, int a){
		return boxRGBA(System::Screen, (Sint16)x1 - CameraX, (Sint16)y1 - CameraY, (Sint16)x2 - CameraX, (Sint16)y2 - CameraY, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a);
	}
	
	int DrawLine(int x1, int y1, int x2, int y2, Uint32 color){
		return lineColor(System::Screen, (Sint16)x1 - CameraX, (Sint16)y1 - CameraY, (Sint16)x2 - CameraX, (Sint16)y2 - CameraY, color);
	}
	int DrawLine(int x1, int y1, int x2, int y2, int r, int g, int b, int a){
		return lineRGBA(System::Screen, (Sint16)x1 - CameraX, (Sint16)y1 - CameraY, (Sint16)x2 - CameraX, (Sint16)y2 - CameraY, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a);
	}
	
	int DrawAALine(int x1, int y1, int x2, int y2, Uint32 color){
		return aalineColor(System::Screen, (Sint16)x1 - CameraX, (Sint16)y1 - CameraY, (Sint16)x2 - CameraX, (Sint16)y2 - CameraY, color);
	}
	int DrawAALine(int x1, int y1, int x2, int y2, int r, int g, int b, int a){
		return aalineRGBA(System::Screen, (Sint16)x1 - CameraX, (Sint16)y1 - CameraY, (Sint16)x2 - CameraX, (Sint16)y2 - CameraY, (Uint8)r, (Uint8)g, (Uint8)b,  a);
	}
	
	int DrawCircle(int x, int y, int r, Uint32 color){
		return circleColor(System::Screen, (Sint16)x - CameraX, (Sint16)y - CameraY, (Uint8)r, color);
	}
	int DrawCircle(int x, int y, int rad, int r, int g, int b, int a){
		return circleRGBA(System::Screen, (Sint16)x - CameraX, (Sint16)y - CameraY, (Uint8)rad, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a);
	}
	
	int DrawAACircle(int x, int y, int r, Uint32 color){
		return aacircleColor(System::Screen, (Sint16)x - CameraX, (Sint16)y - CameraY, (Uint8)r, color);
	}
	int DrawAACircle(int x, int y, int rad, int r, int g, int b, int a){
		return aacircleRGBA(System::Screen, (Sint16)x - CameraX, (Sint16)y - CameraY, (Uint8)rad, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a);
	}
	
	int DrawFilledCircle(int x, int y, int r, Uint32 color){
		return filledCircleColor(System::Screen, (Sint16)x - CameraX, (Sint16)y - CameraY, (Uint8)r, color);
	}
	int DrawFilledCircle(int x, int y, int rad, int r, int g, int b, int a){
		return filledCircleRGBA(System::Screen, (Sint16)x - CameraX, (Sint16)y - CameraY, (Uint8)rad, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a);
	}
	
	int DrawEllipse(int x, int y, int rx, int ry, Uint32 color){
		return ellipseColor(System::Screen, (Sint16)x - CameraX, (Sint16)y - CameraY, (Uint8)rx, (Uint8)ry, color);
	}
	int DrawEllipse(int x, int y, int rx, int ry, int r, int g, int b, int a){
		return ellipseRGBA(System::Screen, (Sint16)x - CameraX, (Sint16)y - CameraY, (Uint8)rx, (Uint8)ry, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a);
	}
	
	int DrawAAEllipse(int x, int y, int rx, int ry, Uint32 color){
		return aaellipseColor(System::Screen, (Sint16)x - CameraX, (Sint16)y - CameraY, (Uint8)rx, (Uint8)ry, color);
	}
	int DrawAAEllipse(int x, int y, int rx, int ry, int r, int g, int b, int a){
		return aaellipseRGBA(System::Screen, (Sint16)x - CameraX, (Sint16)y - CameraY, (Uint8)rx, (Uint8)ry, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a);
	}
	
	int DrawFilledEllipse(int x, int y, int rx, int ry, Uint32 color){
		return filledEllipseColor(System::Screen, (Sint16)x - CameraX, (Sint16)y - CameraY, (Uint8)rx, (Uint8)ry, color);
	}
	int DrawFilledEllipse(int x, int y, int rx, int ry, int r, int g, int b, int a){
		return filledEllipseRGBA(System::Screen, (Sint16)x - CameraX, (Sint16)y - CameraY, (Uint8)rx, (Uint8)ry, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a);
	}
	
	int DrawPie(int x, int y, int rad, int start, int end, Uint32 color){
		return pieColor(System::Screen, (Sint16)x - CameraX, (Sint16)y - CameraY, (Uint8)rad, (Sint16)start, (Sint16)end, color);
	}
	int DrawPie(int x, int y, int rad, int start, int end, int r, int g, int b, int a){
		return pieRGBA(System::Screen, (Sint16)x - CameraX, (Sint16)y - CameraY, (Uint8)rad, (Sint16)start, (Sint16)end, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a);
	}
	
	int DrawFilledPie(int x, int y, int rad, int start, int end, Uint32 color){
		return filledPieColor(System::Screen, (Sint16)x - CameraX, (Sint16)y - CameraY, (Uint8)rad, (Sint16)start, (Sint16)end, color);
	}
	int DrawFilledPie(int x, int y, int rad, int start, int end, int r, int g, int b, int a){
		return filledPieRGBA(System::Screen, (Sint16)x - CameraX, (Sint16)y - CameraY, (Uint8)rad, (Sint16)start, (Sint16)end, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a);
	}
	
	int DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Uint32 color){
		return trigonColor(System::Screen, (Sint16)x1 - CameraX, (Sint16)y1 - CameraY, (Sint16)x2 - CameraX, (Sint16)y2 - CameraY, (Sint16)x3 - CameraX, (Sint16)y3 - CameraY, color);
	}
	int DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int r, int g, int b, int a){
		return trigonRGBA(System::Screen, (Sint16)x1 - CameraX, (Sint16)y1 - CameraY, (Sint16)x2 - CameraX, (Sint16)y2 - CameraY, (Sint16)x3 - CameraX, (Sint16)y3 - CameraY, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a);
	} 
	
	int DrawAATriangle(int x1, int y1, int x2, int y2, int x3, int y3, Uint32 color){
		return aatrigonColor(System::Screen, (Sint16)x1 - CameraX, (Sint16)y1 - CameraY, (Sint16)x2 - CameraX, (Sint16)y2 - CameraY, (Sint16)x3 - CameraX, (Sint16)y3 - CameraY, color);
	}
	int DrawAATriangle( int x1, int y1, int x2, int y2, int x3, int y3, int r, int g, int b, int a){
		return aatrigonRGBA(System::Screen,  x1, (Sint16)y1 - CameraY, (Sint16)x2 - CameraX, (Sint16)y2 - CameraY, (Sint16)x3 - CameraX, (Sint16)y3 - CameraY, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a);
	}
	
	int DrawFilledTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color){
		return filledTrigonColor(System::Screen, (Sint16)x1 - CameraX, (Sint16)y1 - CameraY, (Sint16)x2 - CameraX, (Sint16)y2 - CameraY, (Sint16)x3 - CameraX, (Sint16)y3 - CameraY, color);
	}
	int DrawFilledTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int r, int g, int b, int a){
		return filledTrigonRGBA(System::Screen, (Sint16)x1 - CameraX, (Sint16)y1 - CameraY, (Sint16)x2 - CameraX, (Sint16)y2 - CameraY, (Sint16)x3 - CameraX, (Sint16)y3 - CameraY, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a);
	}



}
}



