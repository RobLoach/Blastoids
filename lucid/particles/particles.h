#if !defined(_LUCID_PARTICLES_H_)
#define _LUCID_PARTICLES_H_

#include "../lucid.h"
#include <string>
#include <list>
#include <SDL/SDL.h>


namespace System{
namespace Graphics{


class Particle {
	private:
	public:
	int m_life;
	int m_startlife;
	virtual void Draw(){ }
	virtual int Alpha(int a){ }
	virtual int Alpha(){ }
	System::Math::Vector2D Velocity;
	virtual void Colour(Uint8 r, Uint8 g, Uint8 b, Uint8 a){ }
	virtual void Load(std::string name, int x, int y, int width, int height){ }

	bool Update();

	virtual double x(){  }
	virtual double x(double i){ }
	virtual double y(){ }
	virtual double y(double i){ }
};

class ParticlePixel : public Particle{
	double m_x, m_y;
	Uint8 m_ColourR, m_ColourG, m_ColourB, m_ColourA;

	public:
	ParticlePixel(int ix, int iy, double angle, double speed, int life, Uint8 r, Uint8 g, Uint8 b) :
			m_x(ix),
			m_y(iy),
			m_ColourR(r), m_ColourG(g), m_ColourB(b), m_ColourA(255)
	{
		this->m_life = life;
		this->m_startlife = life;
		this->Velocity.Direction(angle);
		this->Velocity.Length(speed);
	}

	int Alpha(int a){
		if(a <= 0) 			m_ColourA = 0;
		else if(a > 100) 	m_ColourA = 255;
		else				m_ColourA = (int)(a * 2.55);
		return m_ColourA;
	}
	int Alpha(){ return (int)(m_ColourA / 2.55); }
	void Colour(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
		m_ColourR = r; m_ColourG = g; m_ColourB = b; m_ColourA = a;
	}
	void Draw(){
		System::Graphics::DrawPixel((int)m_x, (int)m_y, m_ColourR, m_ColourG, m_ColourB, m_ColourA);
	}

	double x(){ return m_x; }
	double x(double i){ return m_x = i; }
	double y(){ return m_y; }
	double y(double i){ return m_y = i; }
	
};



class ParticleSprite : public Particle {
	System::Graphics::Sprite m_sprite;
	public:
	ParticleSprite(int ix, int iy, double angle, double speed, int life, std::string name, int imageX, int imageY, int imageWidth, int imageHeight){
		m_sprite.x(ix);
		m_sprite.y(iy);
		this->Velocity.Direction(angle);
		this->Velocity.Length(speed);
		this->m_life = life;
		this->m_startlife = life;
		m_sprite.Load(name, imageWidth, imageHeight);
		m_sprite.Tile(imageX, imageY);
	}
	ParticleSprite(int ix, int iy, double angle, double speed, int life, SDL_Surface* image, int imageX, int imageY, int imageWidth, int imageHeight){
		m_sprite.x(ix);
		m_sprite.y(iy);
		this->Velocity.Direction(angle);
		this->Velocity.Length(speed);
		this->m_life = life;
		this->m_startlife = life;
		m_sprite.TileWidth(imageHeight);
		m_sprite.TileHeight(imageHeight);
		m_sprite.Surface(image);
		m_sprite.Tile(imageX, imageY);
	}

	double x(){ return m_sprite.x(); }
	double x(double i){ return m_sprite.x(i); }
	double y(){ return m_sprite.y(); }
	double y(double i){ return m_sprite.y(i); }
	
	void Draw(){ m_sprite.Draw(); }

	/*void Load(std::string name, int x, int y, int width, int height){
		m_sprite.Load(name, x, y, width, height);
	}*/
	
	int Alpha(int a){
		return m_sprite.Alpha(a);
	}
	
	int Alpha(){
		return m_sprite.Alpha();
	}

};

class ParticleText : public Particle{
	double m_x, m_y;
	Uint8 m_ColourR, m_ColourG, m_ColourB, m_ColourA;
	std::string m_text;
	std::string m_font;

	public:
	std::string Text(std::string text){ return m_text = text; }
	std::string Text(){ return m_text; }
	std::string Font(std::string font){ return m_font = font; }
	std::string Font(){ return m_font; }

	ParticleText(int ix, int iy, double angle, double speed, int life, Uint8 r, Uint8 g, Uint8 b, std::string text, std::string font) :
			m_x(ix),
			m_y(iy),
			m_ColourR(r), m_ColourG(g), m_ColourB(b), m_ColourA(255),
			m_text(text), m_font(font)
	{
		this->m_life = life;
		this->m_startlife = life;
		this->Velocity.Direction(angle);
		this->Velocity.Length(speed);
	}

	int Alpha(int a){
		if(a <= 0) 			m_ColourA = 0;
		else if(a > 100) 	m_ColourA = 255;
		else				m_ColourA = (int)(a * 2.55);
		return m_ColourA;
	}
	int Alpha(){ return (int)(m_ColourA / 2.55); }
	void Colour(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
		m_ColourR = r; m_ColourG = g; m_ColourB = b; m_ColourA = a;
	}
	void Draw(){
		System::Text::Print((int)m_x,(int)m_y,m_text,m_ColourR,m_ColourG,m_ColourB,m_ColourA, 1,1,m_font);
	}

	double x(){ return m_x; }
	double x(double i){ return m_x = i; }
	double y(){ return m_y; }
	double y(double i){ return m_y = i; }
	
};




class ParticleSystem {
public:
	void Update();
	void Draw();
	void Clear();
	
	void AddPixel(int x, int y, double angle, double speed, int life, Uint8 colourR, Uint8 colourG, Uint8 colourB);
	void AddSprite(int x, int y, double angle, double speed, int life, std::string name, int imageX, int imageY, int imageWidth, int imageHeight);
	void AddSprite(int x, int y, double angle, double speed, int life, SDL_Surface* image, int imageX, int imageY, int imageWidth, int imageHeight);
	void AddText(int x, int y, double angle, double speed, int life, Uint8 colourR, Uint8 colourG, Uint8 colourB, std::string text, std::string font = "default");
	
	void AddPixelExplosion(int particles, int x, int y, double speed, double speedChange, int life, int lifeChange, Uint8 colourR, Uint8 colourG, Uint8 colourB);
	
	void AddPixelGun(int particles, int x, int y, double direction, double directionChange, double speed, double speedChange, int life, int lifeChange, Uint8 colourR, Uint8 colourG, Uint8 colourB);

	~ParticleSystem();

private:
	std::list<Particle*> ParticlePool;
};




}
}




#endif
