#if !defined(_PRIMATIVES_H_INCLUDED_)
#define _PRIMATIVES_H_INCLUDED_

#include <SDL/SDL.h>
#include "SDL_gfx/SDL_gfxPrimitives.h"


namespace System{
	extern SDL_Surface *Screen;
	extern int CameraX;
	extern int CameraY;
namespace Graphics{

	Uint32 MakeColour(int r, int g, int b, int a);

	Uint32 MakeColour(int r = 0, int g = 0, int b = 0);
	
	int DrawPixel(int x, int y, Uint32 color);
	int DrawPixel(int x, int y, int r = 0, int g = 0, int b = 0, int a = 255);
	
	int DrawHorizontalLine(int x1, int x2, int y, Uint32 color);
	int DrawHorizontalLine(int x1, int x2, int y, int r = 0, int g = 0, int b = 0, int a = 255);
	
	int DrawVerticalLine(int x, int y1, int y2, Uint32 color);
	int DrawVerticalLine(int x, int y1, int y2, int r = 0, int g = 0, int b = 0, int a = 255);
	
	int DrawRectangle(int x1, int y1, int x2, int y2, Uint32 color);
	int DrawRectangle(int x1, int y1, int x2, int y2, int r = 0, int g = 0, int b = 0, int a = 255);
	
	int DrawFilledRectangle(int x1, int y1, int x2, int y2, Uint32 color);
	int DrawFilledRectangle(int x1, int y1, int x2, int y2, int r = 0, int g = 0, int b = 0, int a = 255);
	
	int DrawLine(int x1, int y1, int x2, int y2, Uint32 color);
	int DrawLine(int x1, int y1, int x2, int y2, int r = 0, int g = 0, int b = 0, int a = 255);
	
	int DrawAALine(int x1, int y1, int x2, int y2, Uint32 color);
	int DrawAALine(int x1, int y1, int x2, int y2, int r = 0, int g = 0, int b = 0, int a = 255);
	
	int DrawCircle(int x, int y, int r, Uint32 color);
	int DrawCircle(int x, int y, int rad, int r = 0, int g = 0, int b = 0, int a = 255);
	
	int DrawAACircle(int x, int y, int r, Uint32 color);
	int DrawAACircle(int x, int y, int rad, int r = 0, int g = 0, int b = 0, int a = 255);
	
	int DrawFilledCircle(int x, int y, int r, Uint32 color);
	int DrawFilledCircle(int x, int y, int rad, int r = 0, int g = 0, int b = 0, int a = 255);
	
	int DrawEllipse(int x, int y, int rx, int ry, Uint32 color);
	int DrawEllipse(int x, int y, int rx, int ry, int r = 0, int g = 0, int b = 0, int a = 255);
	
	int DrawAAEllipse(int x, int y, int rx, int ry, Uint32 color);
	int DrawAAEllipse(int x, int y, int rx, int ry, int r = 0, int g = 0, int b = 0, int a = 255);
	
	int DrawFilledEllipse(int x, int y, int rx, int ry, Uint32 color);
	int DrawFilledEllipse(int x, int y, int rx, int ry, int r = 0, int g = 0, int b = 0, int a = 255);
	
	int DrawPie(int x, int y, int rad, int start, int end, Uint32 color);
	int DrawPie(int x, int y, int rad, int start, int end, int r = 0, int g = 0, int b = 0, int a = 255);
	
	int DrawFilledPie(int x, int y, int rad, int start, int end, Uint32 color);
	int DrawFilledPie(int x, int y, int rad, int start, int end, int r = 0, int g = 0, int b = 0, int a = 255);
	
	int DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Uint32 color);
	int DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int r = 0, int g = 0, int b = 0, int a = 255);
	
	int DrawAATriangle(int x1, int y1, int x2, int y2, int x3, int y3, Uint32 color);
	int DrawAATriangle( int x1, int y1, int x2, int y2, int x3, int y3, int r = 0, int g = 0, int b = 0, int a = 255);
	
	int DrawFilledTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color);
	int DrawFilledTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int r = 0, int g = 0, int b = 0, int a = 255);

}
}


#endif // _PRIMATIVES_H_INCLUDED_


