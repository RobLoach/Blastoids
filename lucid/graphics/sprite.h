
// Sprites

// TODO - Make Default arguments, load from fragment of file.


// Includes
#if !defined(_SPRITE_H_INCLUDED_)
#define _SPRITE_H_INCLUDED_

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h> 
#include <SDL/SDL_image.h>


namespace System{
	extern SDL_Surface *Screen;
	extern int Width;
	extern int Height;
	extern int CameraX;
	extern int CameraY;
namespace Graphics{


class Sprite{
	public:
		
		// Sprite Base
		Sprite(){ Close(); }
		~Sprite(){ Close(); }

		bool Load(std::string imageName, int TileWidth = -1, int TileHeight = -1);
		void Close();
		
		// TODO - Make default arguments

		bool Draw();
		
		// Positioning
		double x(){ return m_x; }
		double y(){ return m_y; }
		double x(double x){ return m_x = x; }
		double y(double y){ return m_y = y; }
		void Position(double ix, double iy){ x(ix); y(iy); }
		SDL_Surface* Surface(){ return pImageSource; }
		SDL_Surface* Surface(SDL_Surface* image){ return pImageSource = image; }

		void MoveX(double dist) { m_x += dist; }
		void MoveY(double dist) { m_y += dist; }

		int Rotate(int dist){ return Rotation(m_angle += dist); }

		int Width(){ return (int)(m_TileWidth * m_zoom); }
		int Height(){ return (int)(m_TileHeight * m_zoom); }
		
		// Alpha
		int Alpha(){ return (int)(m_alpha / 2.55); }
		int Alpha(int alpha){ 
			if(alpha < 0)        alpha = 0;
			else if(alpha > 100) alpha = 100;
			return m_alpha = (int)(alpha * 2.55);
		}

		// Zoom
		double Zoom(){ return m_zoom; }
		double Zoom(double zoom){ return m_zoom += zoom; }
		double ZoomBy(){ return m_zoom; }
		double ZoomBy(double zoom){ return m_zoom += zoom; }
		
		// Rotation
		int Rotation(){ return m_angle; }
		int Rotation(int angle){
			angle = angle % 360;
			if(angle<0) angle += 360;
			return m_angle = angle;
		}

		// Anti-Aliased Smoothing
		bool Smoothing(){ return m_smoothing; }
		bool Smoothing(bool smoothing){ return m_smoothing = smoothing; }
		

		int TileWidth(){ return m_TileWidth; }
		int TileHeight(){ return m_TileHeight; }
		int TileWidth(int width){ m_TileWidth = width; return width; }
		int TileHeight(int height){ m_TileHeight = height; return height; }
		int TileX(){ return m_TileX; }
		int TileX(int tilex);
		int TileY(){ return m_TileY; }
		int TileY(int tiley);
		int IncrementFrame(){
			m_TileX++;
			if(pImageSource){
				if(m_TileX >= pImageSource->w / m_TileWidth){
					m_TileX = 0;
					m_TileY++;
					if(m_TileY >= pImageSource->h / m_TileHeight){
						m_TileY = 0;
					}
				}
			}
			return m_TileX * m_TileY;
		}
		int IncrementFrameX(){
			m_TileX++;
			if(pImageSource)
				if(m_TileX >= pImageSource->w / m_TileWidth)
					m_TileX = 0;
			return m_TileX;
		}
		int IncrementFrameY(){
			m_TileY++;
			if(pImageSource)
				if(m_TileY >= pImageSource->h / m_TileHeight)
					m_TileY = 0;
			return m_TileY;
		}
		int AnimationSpeed();
		int AnimationSpeed(int n);
		bool Animate(){ return m_Animate; }
		bool Animate(bool a){ return m_Animate = a; }


		int Tile(int x, int y){
			TileX(x);
			TileY(y);
		}

		bool CollisionBoundingBox(System::Graphics::Sprite* Other, int offset = 0);
		bool CollisionBoundingCircle(System::Graphics::Sprite* Other, int offset = 0, int radius1 = -1, int radius2 = -1);

		int Left();
		int Right();
		int Top();
		int Bottom();

		int Left(int d){ x(d + Width()/2); return Left(); }
		int Right(int d){ x(d - Width()/2); return Right(); }
		int Top(int d) { y(d + Height()/2); return Top(); }
		int Bottom(int d){ y(d - Height()/2); return Bottom(); }

		void TransColour(int r = -1, int g = 0, int b = 0);

		bool MouseIsOver();

	private:
		double m_x; // X Coordinates on the destination
		double m_y; // Y coordinates on the destination
		int m_alpha; // The alpha (0-255)
		int m_angle; // Angle
		SDL_Surface* pImageSource;
		int m_TileHeight, m_TileWidth;
		int m_TileX, m_TileY;
		int m_AnimationSpeed;
		bool m_Animate;
		Uint32 m_NextFrameTime;
		double m_zoom; // Zoom factor (1 is no zoom)
		bool m_smoothing;

};

}// Close Sprite
}// Close SDLEngine namespace

#endif // _SPRITE_H_INCLUDED_

