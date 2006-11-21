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

#include "player.h"
#include "bullets.h"
#include "states.h"
//#include "lucid/lucid.h"

CPlayer Player;
int Score;
int Level;
System::Graphics::Sprite SpriteLife;



void CPlayer::Initialize(){
	this->Load("Ship",
			System::Script["ShipWidth"].ToInteger(),
			System::Script["ShipHeight"].ToInteger()
	);
	this->TransColour(255,0,255);
	Velocity.x(0);
	Velocity.y(0);
	m_ThrustersOn = false;
	//m_MouseControl = true;
	m_ReloadTime.SetDelay(500);
	m_weapondamage = 2;
	m_shields = 100;
	m_ThrusterPower = 0.5;
	m_hull = 100;
	m_lives = 3;
	HullProgressBar.Initialize();
	ShieldsProgressBar.Initialize();

	SpriteLife.Load("Ship",System::Script["ShipWidth"].ToInteger(),System::Script["ShipHeight"].ToInteger());
	SpriteLife.TileX(2);
	//SpriteLife.TransColour(255,0,255);
	SpriteLife.y(HullProgressBar.y() + SpriteLife.Height()/2);
}

void CPlayer::Fire(){
	Bullets::AddBullet(m_weapondamage-2, (int)(this->x()), (int)(this->y()), DEG2RAD(this->Rotation()+90), 9, 50);
	System::Audio.Play("SoundShoot");
}
void CPlayer::Update(){
	switch(m_status){
	case 1:	// Alive
		//System::Text::Print(0,0,"FDSA",255,0,255);
		if(m_MouseControl){
			if(System::Input::MouseButtonDown(SDL_BUTTON_RIGHT))
				Thrusters(!this->MouseIsOver());
			else
				Thrusters(false);
			System::Math::Vector2D mousepos;
			mousepos.x(System::Input::MouseX() - this->x());
			mousepos.y(System::Input::MouseY() - this->y());
			mousepos.y(-mousepos.y());
			this->Rotation(int(RAD2DEG(mousepos.Direction())-90));
			if(m_ReloadTime.Check()){
				if(System::Input::MouseButtonDown(SDL_BUTTON_LEFT)){
					this->Fire();
					m_ReloadTime.StartTimer();
				}
			}
		} else {
			Thrusters(System::Input::KeyDown(SDLK_UP));
			if(System::Input::KeyDown(SDLK_RIGHT))
				this->Rotate(-10);
			else if(System::Input::KeyDown(SDLK_LEFT))
				this->Rotate(10);
			
			if(m_ReloadTime.Check()){
				if(System::Input::KeyDown(SDLK_SPACE)){
					this->Fire();
					m_ReloadTime.StartTimer();
				}
			}
		}
	
		Velocity.Length(Velocity.Length() - 0.2);
		if(Velocity.Length() < 0) Velocity.Length(0);
	
		if(m_ThrustersOn){
			this->TileX(1);
	
			System::Math::Vector2D Accel;
			Accel.Length(m_ThrusterPower);
			Accel.Direction(DEG2RAD(this->Rotation()+90));
			Accel.y(-Accel.y());
			if(System::Audio.IsPlaying("SoundEngine") == false){
				System::Audio.Play("SoundEngine");
			}
			if(Velocity.Length() < m_ThrusterPower*(double)12){
				Velocity += Accel;
			}
	
			if(HighDetail){
				
				System::Math::Vector2D Location;
				Location.Direction(Accel.Direction());
				Location.Length(this->Width()/-2.5);
				int partX = (int)(this->x()+Location.x());
				int partY = (int)(this->y()+Location.y());
	
				Accel += Velocity;
				double angle = RAD2DEG(Accel.Direction())+180;
				
				Particles.AddPixelGun(30, 
						partX,
						partY,
						angle,
						40, // Direction change
						2.5,	// Speed
						0.5,	// Speed change
						20,		// life
						3,		// life change
						255,50,50
					);
				Particles.AddPixelGun(20, 
						partX,
						partY,
						angle,
						30, // Direction change
						2,	// Speed
						0.5,	// Speed change
						15,		// life
						3,		// life change
						255, 140, 0
					);
				Particles.AddPixelGun(10, 
						partX,
						partY,
						angle,
						20, // Direction change
						1.5,	// Speed
						0,	// Speed change
						10,		// life
						3,		// life change
						255, 215, 0
					);
				
			}
			
	
	
	//int particles, double x, double y, double direction, double directionChange, double speed, double speedChange, int life, int lifeChange, Uint8 colourR, Uint8 colourG, Uint8 colourB){
	
	
		} else {
			this->TileX(0);
		} 
		
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
		//this->RotationAngle(0);
	break;
	case 0:		// dead
	break;
	case 2:		//respawn
		if(m_respawntime.Check()){
			m_status=1;
			System::Audio.Play("SoundPlayerStart");
			Particles.AddPixelExplosion(70,(int)this->x(),(int)this->y(),
				2, 1.5,
				100,30,
				150,150,150);
		}
	break;
	}
}
void CPlayer::Paint(){
	switch(m_status){
	case 0: // dead
		return;
	break;
	case 1: // alive
		this->Draw();
	break;
	case 2: // respawning
		System::Text::Print(System::Width/2,System::Height/2,"Prepare For Level",220,100,0,200,1,1,"Medium");
		System::Text::Print(System::Width/2,System::Height/2+20,System::Text::ToString(Level),30,30,255,200,1,1,"Big");
	break;
	}
	HullProgressBar.Draw();
	ShieldsProgressBar.Draw();

	for(int i = m_lives; i > 0; i--){
		SpriteLife.x(HullProgressBar.x() - i * SpriteLife.Width());
		SpriteLife.Draw();
	}
}
void CPlayer::DealDamage(int d){
	while(d > 0){
		if(m_shields > 0)
			--m_shields;
		else{
			--m_hull;
			if(m_hull <= 0){
				Explode();
			}
		}
		--d;
	}
	HullProgressBar.Value(m_hull);
	ShieldsProgressBar.Value(m_shields);
	if(!System::Audio.IsPlaying("SoundPlayerHit"))
		System::Audio.Play("SoundPlayerHit");
}

void CPlayer::Explode(){
	if(m_status > 0){
		Particles.AddPixelExplosion(75, 
				(int)this->x(), (int)this->y(),
				2, 1.90,	// Speed
				60,	10,		// life
				255,50,50
			);
		Particles.AddPixelExplosion(50, 
				(int)this->x(), (int)this->y(),
				1.5, 1.4,	// Speed
				50,	10,		// life
				255,140,50
			);
		Particles.AddPixelExplosion(25, 
				(int)this->x(), (int)this->y(),
				1, 0.9,	// Speed
				40,	10,		// life
				255,215,50
			);
	
	System::Audio.Play("SoundPlayerExplode");
	
		if(--m_lives <= 0){
			m_status = 0;
			System::SetState(GameOver);
			return;
		}
		this->Hull(100);
		this->Shields(100);
		this->WeaponDamage(2);
		m_ThrusterPower = 0.5;
		PrepareForGame();
	}
}

void CPlayer::PrepareForGame(){
	this->Position(System::Width/2,System::Height/2);
	this->Velocity.Reset();
	this->m_ReloadTime.StartTimer();
	//m_lives = 3;
	m_status = 2;
	m_respawntime.SetDelay(2000);
	m_respawntime.StartTimer();
}





