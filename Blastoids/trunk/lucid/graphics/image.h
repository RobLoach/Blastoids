#if !defined(_IMAGE_H_INCLUDED_)
#define _IMAGE_H_INCLUDED_


#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <string>


namespace System{
namespace Graphics{
namespace Image{
	
	
	class Image;

	void Close();
	void Close(std::string filename);
	bool Load(std::string filename);
	bool Load(std::string name, std::string filename, int x = -1, int y = -1, int width = -1, int height = -1);
	SDL_Surface* GetImage(std::string name);
	void TransColour(std::string name, int r = -1, int g = 0, int b = 0);


	class Image
	{
	public:
		Image() : pImage(NULL) { }
		bool Load(std::string filename, int x = -1, int y = -1, int width = -1, int height = -1);
		void Close();
		~Image() { Close(); }
		SDL_Surface* GetImage(){ return pImage; }
		void TransColour(int r = -1, int g = 0, int b = 0);
		SDL_Surface* pImage;

		int Width(){ if(pImage) return pImage->w; return 0; }
		int Height(){ if(pImage) return pImage->h; return 0; }
	};


}
}
}


#endif // _GRAPHICS_H_INCLUDED_


