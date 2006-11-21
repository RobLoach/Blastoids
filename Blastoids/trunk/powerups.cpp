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

#include "powerups.h"
#include "lucid/lucid.h"
#include "states.h"
#include <list>

namespace PowerUps{

std::list<CPowerUp*> PowerUpPool;

int PowerUpsWidth;
int PowerUpsHeight;


void Clear(){
	while(!PowerUpPool.empty()){
		delete PowerUpPool.back();
		PowerUpPool.pop_back();
	}
	PowerUpPool.clear();

}

void Draw(){
	for(std::list<CPowerUp*>::iterator pos = PowerUpPool.begin(); pos != PowerUpPool.end(); pos++){
		(*pos)->Draw();
	}
}

void Update(){
	for(std::list<CPowerUp*>::iterator pos = PowerUpPool.begin(); pos != PowerUpPool.end(); pos++){
		if((*pos)->Update()){
			delete (*pos);
			PowerUpPool.erase(pos);
			break;
		}
	}
}

bool CPowerUp::Update(){
	//this->MoveX(Velocity.x());
	//this->MoveY(Velocity.y());

	/*
	if(Left() > System::Width) Right(0);
	if(Right() < 0) Left(System::Width);
	if(Top() > System::Height) Bottom(0);
	if(Bottom() < 0) Top(System::Height);
	*/
	
	if(this->CollisionBoundingCircle(&Player,-5)){

			System::Audio.Play("SoundPowerup");
		switch(m_type){
		case 0:
			Player.WeaponDamage(Player.WeaponDamage() + 1);
			Particles.AddText((int)this->x(), (int)this->y(),
				4.712388981, 0.4, 100,
				255,33, 33, 
				"Upgrade", "Small");
			return true;

		case 1:
			Player.Shields(Player.Shields() + 40);
			Particles.AddText((int)this->x(), (int)this->y(),
				4.712388981, 0.4, 100,
				33,33, 230, 
				"Shields", "Small");
			return true;

		case 2:
			Player.Lives(Player.Lives() + 1);
			Particles.AddText((int)this->x(), (int)this->y(),
				4.712388981, 0.4, 100,
				33,230, 230, 
				"Extra Life", "Small");
			return true;

		case 3:
			Score += System::Math::RandomNumber(100,250);
			Particles.AddText((int)this->x(), (int)this->y(),
				4.712388981, 0.4, 100,
				230,230, 33, 
				"Bonus", "Small");
			return true;

		case 4:
			Player.ThrusterPower(Player.ThrusterPower()+0.05);
			Particles.AddText((int)this->x(), (int)this->y(),
				4.712388981, 0.4, 100,
				33, 230, 33, 
				"Thrusters", "Small");
			return true;
//x, int y, double angle, double speed, int life, Uint8 colourR, Uint8 colourG, Uint8 colourB, std::string text, std::string font = "default"
		}
	}

	if(--m_life<0)
		return true;
	
	return false;
}


void AddPowerUp(int x, int y){
	PowerUpPool.push_back(new CPowerUp());
	int type = System::Math::RandomNumber(0,100);

	if(type >= 0 && type <= 15) type = 0;
	if(type > 15 && type <= 30) type = 1;
	if(type > 30 && type <= 35) type = 2;
	if(type > 35 && type <= 50) type = 4;
	if(type > 50 && type <= 100) type = 3;

	PowerUpPool.back()->Init(type, x, y);
}

void CPowerUp::Init(int type, int x, int y){
		this->Load("PowerUps",	PowerUpsWidth,PowerUpsHeight
				//System::Script["BulletWidth"].ToInteger(),
				//System::Script["BulletHeight"].ToInteger()
		);
		this->TileX(m_type = type);
		m_life = 700 + System::Math::RandomNumber(-200, 200);
		this->x(x);
		this->y(y);

}




}
