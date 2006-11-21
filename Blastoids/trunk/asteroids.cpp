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

#include "asteroids.h"
#include "states.h"
#include "player.h"
#include "lucid/lucid.h"
#include "powerups.h"
//#include "lucid/text/encoding.h"

#include <list>


using namespace std;

namespace Asteroids{

	int AsteroidLargeWidth;
	int AsteroidLargeHeight;
	int AsteroidMediumWidth;
	int AsteroidMediumHeight;
	int AsteroidSmallWidth;
	int AsteroidSmallHeight;
	
	list<Asteroid*> AsteroidPool;
	
	
	void Clear(){
		while(!AsteroidPool.empty()){
			delete AsteroidPool.back();
			AsteroidPool.pop_back();
		}
		AsteroidPool.clear();
	}
	
	void Update(){
		for(list<Asteroid*>::iterator pos = AsteroidPool.begin(); pos != AsteroidPool.end(); pos++){
			if((*pos)->Update()){
				Explode(pos);
				break;
			}	
		}
		
/*
		for(list<Asteroid*>::iterator pos = AsteroidPool.begin(); pos != AsteroidPool.end(); pos++){
			for(list<Asteroid*>::iterator pos2 = pos; pos2 != AsteroidPool.end(); pos2++){
				++pos2;
				if(pos2 != AsteroidPool.end()){
					if((*pos)->CollisionBoundingCircle((*pos2), -10)){
						System::Math::Vector2D temp;
						temp = (*pos)->Velocity;
						(*pos)->Velocity -= (*pos2)->Velocity;
						(*pos2)->Velocity -= temp;
					}
				}
			}
		}*/
	}
	
	void Draw(){
		for(list<Asteroid*>::iterator pos = AsteroidPool.begin(); pos != AsteroidPool.end(); pos++){
			(*pos)->Draw();
		}
	}
  
	void AddAsteroid(int size, double x, double y){
		if(size < 0) size = System::Math::RandomNumber(0,2);
		if(x < 0 && y < 0){

			// Come in from edge of screen
			if(System::Math::RandomNumber(0,1) == 1){
				x = System::Math::RandomNumber(0,System::Width);
				if(System::Math::RandomNumber(0,1) == 1)
					y = -AsteroidSmallHeight/2;
				else
					y = System::Height + AsteroidSmallHeight/2;
			} else {
				y = System::Math::RandomNumber(0,System::Height);
				if(System::Math::RandomNumber(0,1) == 1)
					x = -AsteroidSmallWidth/2;
				else
					x = System::Width + AsteroidSmallWidth/2;
			}
		}
		AsteroidPool.push_back(new Asteroid());
		AsteroidPool.back()->Init(size,x,y);
	}
	
	
	bool Asteroid::Update(){
		this->MoveX(Velocity.x());
		this->MoveY(Velocity.y());
	
		if(this->x() + this->Width()/2 < 0) { // left
			this->x(System::Width + this->Width()/2);
		} else if(this->y() + this->Height()/2 < 0){ // top
			this->y(System::Height + this->Height()/2);
		} else if(this->x() - this->Width()/2 > System::Width){ // right
			this->x(0 - this->Width()/2);
		} else if(this->y() - this->Height()/2 > System::Height){
			this->y(0 - this->Height()/2);
		}
	
		if(HighDetail)
			this->Rotate(AngleOfRotation);
		else
			this->Rotation(0);

		if(Player.Status() == 1){
			if(Player.CollisionBoundingCircle(this, -10)){
				switch(Size){
				case 0:	Player.DealDamage(30);
				break;
				case 1: Player.DealDamage(25);
				break;
				case 2: Player.DealDamage(20);
				break;
				}
				return true;
			}
		}
		return false;
	}

	void Asteroid::Init(int size, double x, double y){
		switch(size){
		case 0:
			this->Load("AsteroidsLarge",AsteroidLargeWidth,AsteroidLargeHeight
					//System::Script["AsteroidsLargeWidth"].ToInteger(),
					//System::Script["AsteroidsLargeHeight"].ToInteger()
			);
			Health = 12;
		break;
		case 1:
			this->Load("AsteroidsMedium",AsteroidMediumWidth,AsteroidMediumHeight
					//System::Script["AsteroidsMediumWidth"].ToInteger(),
					//System::Script["AsteroidsMediumHeight"].ToInteger()
				//80,80
			);
			Health = 6;
		break;
		case 2:
			this->Load("AsteroidsSmall",AsteroidSmallWidth,AsteroidSmallHeight
					//30,30
					//System::Script["AsteroidsSmallWidth"].ToInteger(),
					//System::Script["AsteroidsSmallHeight"].ToInteger()
			);
			Health = 1;
		break;
		}
		Size = size;
		AngleOfRotation = System::Math::RandomNumber(-5,5);
		Velocity.Direction(DEG2RAD(System::Math::RandomNumber(0,360)));
		Velocity.Length(System::Math::RandomNumber(2,5));
		this->TileX(-1);
		this->Position(x, y);
	}
	

	void Explode(list<Asteroid*>::iterator &pos){
		(*pos)->Health -= Player.WeaponDamage();
		if((*pos)->Health <= 0){
			int scoreawarded;
			switch((*pos)->Size){
			case 0:
				AddAsteroid(1, (*pos)->x(), (*pos)->y());
				AddAsteroid(1, (*pos)->x(), (*pos)->y());
				//AddAsteroid(1, (*pos)->x(), (*pos)->y());
				Particles.AddPixelExplosion(250,(int)(*pos)->x(),(int)(*pos)->y(),
						3,1,
						40,20,
						150,150,150);
				scoreawarded = System::Math::RandomNumber(80,120);
				for(int num = 0; num < 3; num++){
					PowerUps::AddPowerUp(
						(int)(*pos)->x() + System::Math::RandomNumber(-AsteroidLargeWidth/3,AsteroidLargeWidth/3),
						(int)(*pos)->y() + System::Math::RandomNumber(-AsteroidLargeHeight/3,AsteroidLargeHeight/3)
					);
				}
				//Particles.AddPixelExplosion()
			break;
			case 1:
				AddAsteroid(2, (*pos)->x(), (*pos)->y());
				AddAsteroid(2, (*pos)->x(), (*pos)->y());
				AddAsteroid(2, (*pos)->x(), (*pos)->y());
				//AddAsteroid(2, (*pos)->x(), (*pos)->y());
				Particles.AddPixelExplosion(200,(int)(*pos)->x(),(int)(*pos)->y(),
						3,1,
						40,20,
						150,150,150);
				scoreawarded = System::Math::RandomNumber(30,50);
				PowerUps::AddPowerUp((int)(*pos)->x(),(int)(*pos)->y());
			break;
			case 2:
				Particles.AddPixelExplosion(150,(int)(*pos)->x(),(int)(*pos)->y(),
						3,1,
						30,5,
						150,150,150);
				scoreawarded = System::Math::RandomNumber(5,15);
				//PowerUps::AddPowerUp((int)(*pos)->x(),(int)(*pos)->y());
			break;
			}
			Score+=scoreawarded;

			System::Audio.Play("SoundAsteroidExplode");
			Particles.AddText((int)(*pos)->x(), (int)(*pos)->y(),
				4.712388981, 0.4, 60,
				200, 0, 0, 
				System::Text::ToString(scoreawarded), "Small");
			//if(*pos){
			delete (*pos);
			AsteroidPool.erase(pos);
	
			if(AsteroidPool.empty()){
				LevelUp();
			}
			return;
			//}

		
		}
		// Nothing
		
	}




}
