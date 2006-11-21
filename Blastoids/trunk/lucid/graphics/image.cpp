#include "image.h"

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <string>
#include <map>
#include <SDL/SDL_image.h>
#include "SDL_gfx/SDL_rotozoom.h"


namespace System{
namespace Graphics{
namespace Image{
	

	std::map<std::string, Image*> ImageData;
	typedef std::map<std::string, Image*>::iterator ImageDataItem;

	Image* get(std::string name) {
		ImageDataItem it = ImageData.find(name);
		if (it == ImageData.end()) return NULL;
		return it->second;
	}

	
	void Close(){
		for(ImageDataItem pos = ImageData.begin(); pos != ImageData.end(); pos++){
			if((*pos).second){
				(*pos).second->Close();
				delete (*pos).second;
			}
			//pos->second->Close();
		}
		ImageData.clear();
	}

	void Close(std::string name){
		ImageDataItem it = ImageData.find(name);
		if(it != ImageData.end()){
			if(it->second)
				 it->second->Close();
			ImageData.erase(it);
		}
	}



	bool Load(std::string filename){
		Image* img = get(filename);
		if(img)
			return true;
		
		img = new Image();
		if(img->Load(filename)){
			ImageData[filename] = img;
			return true;
		} else {
			delete img;
			return false;
		}
	}

	bool Load(std::string name, std::string filename, int x, int y, int width, int height){
		Image* img = get(name);
		if(img)
			return true;
		img = new Image();
		if(img->Load(filename,x,y,width,height)){
			ImageData[name] = img;
			return true;
		} else {
			delete img;
			return false;
		}
	}

	SDL_Surface* GetImage(std::string name){
		Image* img = get(name);
		if(img)
			return img->GetImage();
		if(Load(name)){
			img = get(name);
			if(img)
				return img->GetImage();
		}
		return NULL;
	}


	bool Image::Load(std::string filename, int x, int y, int width, int height){

		if((x<0) && (y<0) && (width<0) && (height<0))
			return ((pImage = IMG_Load(filename.c_str())) != NULL);

		SDL_Surface* tempImage = IMG_Load(filename.c_str());
		if(tempImage == NULL)
			return false;

		// Find out how big the surface should be
		if(x < 0)				x = 0;
		if(y < 0)				y = 0;
		if(x > tempImage->w)	x = 0;
		if(y > tempImage->h)	y = 0;

		if(width <= 0)	width = tempImage->w - x;
		if(height <= 0)	height = tempImage->h - y;

		if(x + width > tempImage->w)	width = tempImage->w - x;
		if(y + height > tempImage->h)	height = tempImage->h - y;

		SDL_SetColorKey(tempImage, 0, 0);
		
		// Create a new surface to copy over the required image data		
		SDL_Surface* surface = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCCOLORKEY|SDL_SRCALPHA, width, height, 32, tempImage->format->Rmask, tempImage->format->Gmask, tempImage->format->Bmask, tempImage->format->Amask);
		if(surface == NULL){
			SDL_FreeSurface(tempImage);
			return false;
		}

		//SDL_SetColorKey(surface, 0, 0);
		SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, 255, 0, 255, 255));
		
		//SDL_SetColorKey(surface, SDL_SRCCOLORKEY, SDL_MapRGB(surface->format, tempImage->format->Rmask, tempImage->format->Gmask, tempImage->format->Bmask));
		SDL_Rect source;
		source.x = x; source.y = y;
		source.w = width; source.h = height;
	    SDL_BlitSurface(tempImage, &source, surface, NULL);

		// Finish up
		SDL_FreeSurface(tempImage);


		pImage = surface;
		this->TransColour();
		return true;
	}	

	void Image::Close() {
		if(pImage){
			SDL_FreeSurface(pImage);
			pImage = NULL;
		}
	}


	
	void Image::TransColour(int r, int g, int b){
		if(pImage){
			if(r<=-1){
				SDL_SetColorKey(pImage, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(pImage->format, 255, 0, 255));
				return;
			}
			SDL_SetColorKey(pImage, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(pImage->format, r, g, b));
		}
	}


	
	void TransColour(std::string name, int r, int g, int b){
		Image* img = get(name);
		if(img)
			img->TransColour(r,g,b);
	}

	
}
}
}
