/*******************************************************************************
 * Title:
 *		Blastoids
 *
 * Author:
 *		Rob Loach	( http://www.robloach.net )
 *
 * Description:
 *		A simple asteroids clone.
 * 
 * License:
 * 		Blastoids - a simple asteroids clone
 * 		Copyright (C) 2005 Rob Loach
 * 		
 * 		This program is free software; you can redistribute it and/or modify
 * 		it under the terms of the GNU General Public License as published by
 * 		the Free Software Foundation; either version 1, or (at your option)
 * 		any later version.
 * 		
 * 		This program is distributed in the hope that it will be useful,
 * 		but WITHOUT ANY WARRANTY; without even the implied warranty of
 * 		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * 		GNU General Public License for more details.
 * 		
 * 		You should have received a copy of the GNU General Public License
 * 		along with this program; if not, write to the Free Software
 * 		Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 * 
/******************************************************************************/

#include "bullets.h"
#include "player.h"
#include "states.h"

#include "asteroids.h"

#include <list>

namespace Bullets{
int BulletWidth;
int BulletHeight;

std::list<Bullet*> BulletPool;

void Clear(){
	while(!BulletPool.empty()){
		delete BulletPool.back();
		BulletPool.pop_back();
	}
	BulletPool.clear();
}

void AddBullet(int type, int x, int y, double direction, double speed, int life){
	BulletPool.push_back(new Bullet());
	BulletPool.back()->Init(type,x,y,direction,speed, life);
}

void Draw(){
	for(std::list<Bullet*>::iterator pos = BulletPool.begin(); pos != BulletPool.end(); pos++){
		(*pos)->Draw();
	}
}



void Update(){
	for(std::list<Bullet*>::iterator pos = BulletPool.begin(); pos != BulletPool.end(); pos++){
		if((*pos)->Update()){


			Particles.AddPixelExplosion(
					50, // number
					(int)(*pos)->x(), (int)(*pos)->y(),
					1.3, 	0.5,	// speed
					20, 	5,		// life
					255, 153, 0);

			delete (*pos);
			BulletPool.erase(pos);
			break;
		}
	}
}



void Bullet::Init(int type, int x, int y, double direction, double speed, int life){
	this->Load("Bullets",	BulletWidth,BulletHeight
			//System::Script["BulletWidth"].ToInteger(),
			//System::Script["BulletHeight"].ToInteger()
	);
	this->TileX(type);
	this->x(x);
	this->y(y);
	Velocity.Direction(direction);
	Velocity.Length(speed);
	Velocity.y(-Velocity.y());
	Life = life;
}

bool Bullet::Update(){
	this->MoveX(Velocity.x());
	this->MoveY(Velocity.y());

	if(Left() > System::Width) Right(0);
	if(Right() < 0) Left(System::Width);
	if(Top() > System::Height) Bottom(0);
	if(Bottom() < 0) Top(System::Height);

	if(--Life<0)
		return true;
	
	for(list<Asteroids::Asteroid*>::iterator pos = Asteroids::AsteroidPool.begin(); pos != Asteroids::AsteroidPool.end(); pos++){
		if(this->CollisionBoundingCircle((*pos), -10)){
			Asteroids::Explode(pos);
			System::Audio.Play("SoundAsteroidHit");
			return true;
		}
	}
	return false;
}



}
