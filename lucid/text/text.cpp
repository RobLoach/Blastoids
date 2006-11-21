#include "text.h"

#include "../file/file.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <map>
#include <vector>

using namespace std;

namespace System{
	extern SDL_Surface *Screen;
	extern int CameraX;
	extern int CameraY;
 
namespace Text{

	std::string DefaultFont;
	map<string, TTF_Font*> m_Fonts;
	typedef map<string, TTF_Font*>::iterator FontIterator;



	TTF_Font* GetFont(std::string key){
		FontIterator pos = m_Fonts.find(key);
		if (pos == m_Fonts.end()) return NULL;
		return pos->second;
	}

	void CloseFont(TTF_Font* font){
		if(font != NULL){
			TTF_CloseFont(font);
			font = NULL;
		}
	}

	void CloseFont(std::string key){
		CloseFont(GetFont(key));
		FontIterator pos = m_Fonts.find(key);
		if (pos == m_Fonts.end()) return;
		m_Fonts.erase(pos);
	}



	bool Initialize(){
		if(TTF_Init() == -1)
			return false;
		return true;
	}

	void Close(){
		for(FontIterator pos = m_Fonts.begin(); pos != m_Fonts.end(); ++pos){
			CloseFont(pos->second);
    	}
		TTF_Quit();
	}

	bool LoadFont(std::string key, std::string filename, int fontSize){
		bool exists = true;
		//fstream fin; 
		//fin.open(filename.c_str(),ios::in);
		//exists = fin.is_open();
		//fin.close();
		if(System::File::Exists(filename)){
			TTF_Font* font = TTF_OpenFont(filename.c_str(), fontSize);
			if(font == NULL){
				printf("TTF_OpenFont: %s\n", TTF_GetError());
				return false;
			}
			m_Fonts[key] = font;
			DefaultFont = key;
			return true;
		}
		return false;
	}

	SDL_Surface* MakeTextSurface(std::string text, TTF_Font* font, int r, int g, int b){
		SDL_Surface* txtSurface;
		SDL_Color colour = {r,g,b,0};
		if(!(txtSurface = TTF_RenderText_Solid(font,text.c_str(), colour))){
			printf("TTF_Print: %s\n", TTF_GetError());
			if(txtSurface != NULL)
				SDL_FreeSurface(txtSurface);
			return NULL;
		}
		return txtSurface;
	}

	int FontHeight(std::string key){
		TTF_Font *font = GetFont(key);
		if(font != NULL) return TTF_FontHeight(font);
		return 0;
	}


	bool Print(int x, int y, std::string text, int r, int g, int b, int a, int halign, int valign, std::string fontKey){
		if(a <= 0) return true;
		if(text.length() <= 0)
			return true;
		/*
			FIND THE FONT
		*/
		TTF_Font* FontTTF;
		if(fontKey == "default")
			FontTTF = GetFont(DefaultFont);
		else
			FontTTF = GetFont(fontKey);
		if(FontTTF == NULL){ // Choose any font if there isn't a default
			for(FontIterator pos = m_Fonts.begin(); pos != m_Fonts.end(); ++pos){
				FontTTF = GetFont(pos->first);
				if(FontTTF != NULL)
					break;
	    	}
		}
		if(FontTTF == NULL)	return false; // exit if there isn't font

		// Create the surface and paint
		SDL_Surface* txtSurface = MakeTextSurface(text, FontTTF,r,g,b);
		if(txtSurface != NULL){
			SDL_Rect dest; 
			switch(halign){
			case 1: // Center
				dest.x = x - (int)(txtSurface->w/2); 
				break; 
			case 2: // Right
				dest.x = x - (int)txtSurface->w;
				break;
			default: // Left
		    	dest.x = x;
			}
			switch(valign){
			case 1: // Center
				dest.y = y - (int)(txtSurface->h/2);
				break;
			case 2: // Bottom
				dest.y = y - (int)txtSurface->h;
				break;
			default: // Top
				dest.y = y;
			}
			dest.x -= System::CameraX;
			dest.y -= System::CameraY;
			if(a < 255)
				SDL_SetAlpha(txtSurface, SDL_SRCALPHA, a);
		    SDL_BlitSurface(txtSurface, NULL, System::Screen, &dest);
			SDL_FreeSurface(txtSurface);
			return true;
		} else {
			return false;
		}
	}

	

}
}



