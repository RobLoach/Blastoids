#if !defined(_TEXT_H_INCLUDED_)
#define _TEXT_H_INCLUDED_

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

using namespace std;

namespace System{
namespace Text{

	// DefaultFont - The default font to use.
	//  Optionally set this after you have loaded all required fonts
	extern std::string DefaultFont;

	bool Initialize();
	void Close();

	// LoadFont - Loads a font into memory
	//  Key - What you'll refer to the font as when using it (the name)
	//  Filename - The filename of the font
	//  FontSize - The size of the font
	//  CheckExists - Checks if the file exists before attempting to load
	bool LoadFont(std::string key, std::string filename, int fontSize=16);

	// CloseFont - Closes the font (not required as it is managed)
	void CloseFont(std::string key);

	int FontHeight(std::string key);

	// Print - Prints on the screen
	//  x, y - The location to print
	//  text - The text to write
	//  r, g, b - The colour to paint
	//  alignment - 0=left, 1=center, 2=right
	//  fontKey - The font to use (the name)
	bool Print(int x = 0, int y = 0, std::string text = "Hello World", int r = 255, int g = 255, int b = 255, int a = 255, int halign = 0, int valign = 0, std::string fontKey = "default");

}
}


#endif // _TEXT_H_INCLUDED_


