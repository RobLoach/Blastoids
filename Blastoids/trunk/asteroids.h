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

#if !defined(_ASTEROIDS_H_)
#define _ASTEROIDS_H_

#include "lucid/lucid.h"

#include <list>

namespace Asteroids{

class Asteroid : public System::Graphics::Sprite {
	public:
	bool Update();
	void Init(int size, double x, double y);

	int Size;
	System::Math::Vector2D Velocity;
	int AngleOfRotation;
	int Health;
private:
};

void Explode(list<Asteroid*>::iterator &pos);
void Update();
void Draw();
void AddAsteroid(int size=-1, double x=-1, double y=-1);
void Clear();

extern list<Asteroid*> AsteroidPool;
extern int AsteroidLargeWidth;
extern int AsteroidLargeHeight;
extern int AsteroidMediumWidth;
extern int AsteroidMediumHeight;
extern int AsteroidSmallWidth;
extern int AsteroidSmallHeight;

}

#endif
