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

#if !defined(_PLAYER_H_)
#define _PLAYER_H_

#include "lucid/lucid.h"


class CHullProgressBar : public System::GUI::ProgressBar {
public:
	void Initialize(){
		this->y(20);
		this->Width(150);
		this->Height(10);
		this->x(System::Width - 20 - this->Width());
		this->BackColour(255,50,50,50);
		this->BarColour(255,50,50,150);
		this->BorderColour(0,0,0,255);
		this->MaxValue(100);
		this->Value(100);
	}
};

class CShieldsProgressBar : public System::GUI::ProgressBar {
public:
	void Initialize(){
		this->y(30);
		this->Width(150);
		this->Height(10);
		this->x(System::Width - 20 - this->Width());
		this->BackColour(50,50,255,50);
		this->BarColour(50,50,255,150);
		this->BorderColour(0,0,0,255);
		this->MaxValue(100);
		this->Value(100);
	}
};



class CPlayer : public System::Graphics::Sprite {
public:
	CPlayer() : m_status(0) { }
	void Initialize();
	void PrepareForGame();
	void Fire();
	void Paint();

	bool Thrusters(bool t){ return m_ThrustersOn = t; }
	bool Thrusters(){ return m_ThrustersOn; }

	double ThrusterPower(double t){ return m_ThrusterPower = t; }
	double ThrusterPower(){ return m_ThrusterPower; }
	
	System::Math::Vector2D Velocity;
	
	void Update();

	void Explode();

	bool MouseControl(){ return m_MouseControl; }
	bool MouseControl(bool m){ return m_MouseControl = m; }

	int Status(){ return m_status; }
	int Status(int s){ return m_status = s; }

	int WeaponDamage(int d){ this->TileX(d-2); return m_weapondamage = d; }
	int WeaponDamage(){ return m_weapondamage; }

	int Shields(){ return m_shields; }
	int Shields(int s){
		if(s > 100) s = 100;
		if(s < 0) s = 0;
		ShieldsProgressBar.Value(m_shields = s);
		return m_shields;
	}

	int Hull(){ return m_hull; }
	int Hull(int h){ 
		HullProgressBar.Value(m_hull = h);
		return m_hull;
	}

	int Lives(){ return m_lives; }
	int Lives(int l){ 
		return m_lives = l;
	}

	void DealDamage(int d);

private:
	bool m_ThrustersOn;
	double m_ThrusterPower;
	bool m_MouseControl;
	System::Time::Timer m_ReloadTime;
	int m_status;
	int m_weapondamage;
	int m_hull;
	int m_shields;
	int m_lives;
	CHullProgressBar HullProgressBar;
	CShieldsProgressBar ShieldsProgressBar;
	System::Time::Timer m_respawntime;
};

extern CPlayer Player;
extern int Score;
extern int Level;


#endif

