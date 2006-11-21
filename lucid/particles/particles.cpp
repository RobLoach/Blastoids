#include "particles.h"

#include <SDL/SDL.h>
#include "../math/math.h"

namespace System{
namespace Graphics{



bool Particle::Update(){
	if(--m_life <= 0)
		return true;
	x(x() + Velocity.x());
	y(y() + Velocity.y());
	this->Alpha( (int)(  (m_life*100)/(m_startlife)   ) );
	return false;
}



void ParticleSystem::Update(){
	std::list<Particle*>::iterator i = ParticlePool.begin();
	std::list<Particle*>::iterator next;
	while (i != ParticlePool.end()){
		next = i;
		++next;  // pre-increment is more efficient
		if((*i)->Update()){
			delete (*i);
			ParticlePool.erase(i);
		}
		i = next;
	}
}




void ParticleSystem::Draw(){
	for(std::list<Particle*>::iterator pos = ParticlePool.begin(); pos != ParticlePool.end(); pos++){
		(*pos)->Draw();
	}
}

void ParticleSystem::Clear(){
	while(!ParticlePool.empty()){
		delete ParticlePool.back();
		ParticlePool.pop_back();
	}
	ParticlePool.clear();
}

void ParticleSystem::AddPixel(int x, int y, double angle, double speed, int life, Uint8 colourR, Uint8 colourG, Uint8 colourB){
	ParticlePool.push_back(new ParticlePixel(x, y, angle, speed, life, colourR, colourG, colourB));
	

}

void ParticleSystem::AddSprite(int x, int y, double angle, double speed, int life, std::string name, int imageX, int imageY, int imageWidth, int imageHeight){
	ParticlePool.push_back(new ParticleSprite(x, y, angle, speed, life, name, imageX, imageY, imageWidth, imageHeight));
	

}

void ParticleSystem::AddSprite(int x, int y, double angle, double speed, int life, SDL_Surface* image, int imageX, int imageY, int imageWidth, int imageHeight){
	ParticlePool.push_back(new ParticleSprite(x, y, angle, speed, life, image, imageX, imageY, imageWidth, imageHeight));
	

}

void ParticleSystem::AddText(int x, int y, double angle, double speed, int life, Uint8 colourR, Uint8 colourG, Uint8 colourB, std::string text, std::string font){
	ParticlePool.push_back(new ParticleText(x, y, angle, speed, life, colourR, colourG, colourB, text, font));
	

}


void ParticleSystem::AddPixelExplosion(int particles, int x, int y, double speed, double speedChange, int life, int lifeChange, Uint8 colourR, Uint8 colourG, Uint8 colourB){
	for(int i = 0; i < particles; i++){
		AddPixel(
				x,
				y,
				DEG2RAD(System::Math::RandomNumber(0,360)),
				speed + System::Math::RandomNumberDouble(-speedChange, speedChange), 
				life + System::Math::RandomNumber(-lifeChange, lifeChange),
				colourR,
				colourG,
				colourB
			);
	}
}


ParticleSystem::~ParticleSystem(){
	Clear();
}


void ParticleSystem::AddPixelGun(int particles, int x, int y, double direction, double directionChange, double speed, double speedChange, int life, int lifeChange, Uint8 colourR, Uint8 colourG, Uint8 colourB){
	for(int i = 0; i < particles; i++){
		AddPixel(
				x,
				y,
				DEG2RAD(direction + System::Math::RandomNumberDouble(-directionChange,directionChange)),
				speed + System::Math::RandomNumberDouble(-speedChange, speedChange), 
				life + System::Math::RandomNumber(-lifeChange, lifeChange),
				colourR,
				colourG,
				colourB
			);
	}
}


/*
class Particle {


};
*/





}
}

