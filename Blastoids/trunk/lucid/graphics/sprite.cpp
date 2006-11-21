

// Includes
#include "sprite.h"
#include "image.h"
#include "../input/mouse.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "SDL_gfx/SDL_rotozoom.h"
#include "../math/rand.h"


namespace System{
namespace Graphics{

	 
	// Load
	// Loads a bitmap image into the surface
	bool Sprite::Load(std::string imageName, int TileWidth, int TileHeight){
		Close();
		pImageSource = System::Graphics::Image::GetImage(imageName);
		if(pImageSource){ 
			if(TileWidth < 0)
				m_TileWidth = pImageSource->w;
			else 
				m_TileWidth = TileWidth;
			if(TileHeight < 0)
				m_TileHeight = pImageSource->h;
			else
				m_TileHeight = TileHeight;
			return true;
		} else {
			return false;
		}
	}
	
	void Sprite::Close(){
		pImageSource = NULL;
		m_x = System::Width / 2;
		m_y = System::Height / 2;
		m_alpha = 255;
		m_angle = 0;
		m_TileHeight = -1;
		m_TileWidth = -1;
		m_TileX = 0; m_TileY = 0;
		m_AnimationSpeed = -1;
		m_zoom = 1;
		m_smoothing = false;
		m_Animate = false;
	}
 
	// Collision
	bool Sprite::CollisionBoundingBox(System::Graphics::Sprite* Other, int offset){
		if (Bottom() - Other->Top() <= offset) return false;
		if (Other->Bottom() - Top() <= offset) return false;
		if (Right() - Other->Left() <= offset) return false;
		if (Other->Right() - Left() <= offset) return false;
		return true;
	}

	bool Sprite::CollisionBoundingCircle(System::Graphics::Sprite* Other, int offset, int radius1, int radius2){
		if(radius1 < 0) radius1 = Width()/2;
		if(radius2 < 0) radius2 = Other->Width()/2;
		int distx = abs((int)(m_x - Other->x()));
		int disty = abs((int)(m_y - Other->y()));
		return(sqrt((distx * distx) + (disty * disty)) - radius1 - radius2 <= offset);
	}
	
	// Draw
	// Paints the surface onto the destination
	bool Sprite::Draw(){
		if(m_Animate){
			if(m_AnimationSpeed > 0){
				Uint32 now = SDL_GetTicks();
				if(m_NextFrameTime <= now){
					IncrementFrameX();
					m_NextFrameTime = now + m_AnimationSpeed;
				}
			}
		}
		if(m_alpha <= 0) return true; // Invisible
		if(pImageSource){

			//SDL_SetAlpha(pImageSource, SDL_SRCALPHA, m_alpha);
			if(m_TileWidth >= pImageSource->w && m_TileHeight >= pImageSource->h && m_TileX == 0 && m_TileY == 0){
				if(m_angle != 0 || m_zoom != 1){ // Just rotated/zoomed
					
					SDL_SetAlpha(pImageSource, SDL_SRCALPHA, 255);
					SDL_Surface* pImageOutput = rotozoomSurface(pImageSource, m_angle, m_zoom, m_smoothing);
					if(pImageOutput != NULL){
						SDL_SetColorKey(pImageOutput, SDL_SRCCOLORKEY, pImageSource->format->colorkey);
						SDL_SetAlpha(pImageOutput, SDL_SRCALPHA, m_alpha);
					    SDL_Rect dest;
						dest.x = (int)m_x - pImageOutput->w/2 - System::CameraX;
						dest.y = (int)m_y - pImageOutput->h/2 - System::CameraY;
					    SDL_BlitSurface(pImageOutput, NULL, System::Screen, &dest);
						SDL_FreeSurface(pImageOutput);
						return true;
					}

				} else { // No rotation or zoom - fast
				    SDL_Rect dest;
					dest.x = (int)m_x - pImageSource->w/2 - System::CameraX;
					dest.y = (int)m_y - pImageSource->h/2 - System::CameraY;
					SDL_SetAlpha(pImageSource, SDL_SRCALPHA, m_alpha);
				    SDL_BlitSurface(pImageSource, NULL, System::Screen, &dest);
					return true;
				}
			} else { // Different tile
				if(m_angle != 0 || m_zoom != 1){ // Rotated/zoomed and different tile

					SDL_Surface* pImageTile = SDL_CreateRGBSurface(SDL_SWSURFACE|SDL_SRCCOLORKEY, m_TileWidth, m_TileHeight, pImageSource->format->BitsPerPixel,
                                   pImageSource->format->Rmask, pImageSource->format->Gmask, pImageSource->format->Bmask, pImageSource->format->Amask);
					if(pImageTile){
						
						SDL_Rect source;
						source.x = m_TileX * m_TileWidth;
						source.y = m_TileY * m_TileHeight;
						source.w = m_TileWidth;
						source.h = m_TileHeight;

						SDL_SetAlpha(pImageSource, SDL_SRCALPHA, 255);
						SDL_FillRect(pImageTile, NULL, pImageSource->format->colorkey);
						SDL_BlitSurface(pImageSource, &source, pImageTile, NULL);
						SDL_SetColorKey(pImageTile, SDL_SRCCOLORKEY, pImageSource->format->colorkey);
						SDL_Surface* pImageOutput = rotozoomSurface(pImageTile, m_angle, m_zoom, m_smoothing);
						SDL_FreeSurface(pImageTile);

						if(pImageOutput){
						    SDL_Rect dest;
							dest.x = (int)m_x - pImageOutput->w/2 - System::CameraX;
							dest.y = (int)m_y - pImageOutput->h/2 - System::CameraY;

							SDL_SetColorKey(pImageOutput, SDL_SRCCOLORKEY, pImageSource->format->colorkey);
							SDL_SetAlpha(pImageOutput, SDL_SRCALPHA, m_alpha);
						    SDL_BlitSurface(pImageOutput, NULL, System::Screen, &dest);
							SDL_FreeSurface(pImageOutput);
							return true;
						}
					}
				} else { // Just different tile
					SDL_Rect source; source.x = m_TileX * m_TileWidth; source.y = m_TileY * m_TileHeight;
					source.w = m_TileWidth; source.h = m_TileHeight;
				    SDL_Rect dest;
					dest.x = (int)m_x - m_TileWidth/2 - System::CameraX;
					dest.y = (int)m_y - m_TileHeight/2 - System::CameraY;

					SDL_SetAlpha(pImageSource, SDL_SRCALPHA, m_alpha);
				    SDL_BlitSurface(pImageSource, &source, System::Screen, &dest);
					return true;
				}
				
				
			}
				
		}
		return false;


	}

	
	void Sprite::TransColour(int r, int g, int b){
		if(pImageSource){
			if(r<=-1){
			SDL_SetColorKey(pImageSource, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(pImageSource->format, 255, 0, 255));
				return;
			}
			SDL_SetColorKey(pImageSource, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(pImageSource->format, r, g, b));
		}
	}

	int Sprite::Left(){ return (int)((int)m_x - Width()/2); }
	int Sprite::Right(){ return (int)((int)m_x + Width()/2); }
	int Sprite::Top(){ return (int)((int)m_y - Height()/2); }
	int Sprite::Bottom(){ return (int)((int)m_y + Height()/2); }



	
	int Sprite::AnimationSpeed(){ return m_AnimationSpeed; }
	int Sprite::AnimationSpeed(int n){

		if(n>0){
			m_NextFrameTime = SDL_GetTicks() + n;
			return m_AnimationSpeed = n;
		} else {
			return -1;
		}

	}

	int Sprite::TileX(int tilex){
		if(pImageSource){
			int numAvailableTiles = pImageSource->w / m_TileWidth;
			if(tilex < 0){
				m_TileX = System::Math::RandomNumber(0,numAvailableTiles-1);
			} else if(tilex >= numAvailableTiles){
				m_TileX = 0;
			} else {
				m_TileX = tilex;
			}
			return m_TileX;
		}
		return m_TileX = tilex;
	}

	int Sprite::TileY(int tiley){
		if(pImageSource){
			int numAvailableTiles = pImageSource->h / m_TileHeight;
			if(tiley < 0){
				m_TileY = System::Math::RandomNumber(0,numAvailableTiles-1);
			} else if(tiley >= numAvailableTiles){
				m_TileY = 0;
			} else {
				m_TileY = tiley;
			}
			return m_TileX;
		}
		return m_TileY = tiley;
	}

	bool Sprite::MouseIsOver(){
		return System::Input::MouseInBounds(Left(), Top(), Right(), Bottom());
	}

}
}
