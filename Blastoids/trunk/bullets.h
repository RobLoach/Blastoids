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

#if !defined(_BULLETS_H_)
#define _BULLETS_H_

#include "lucid/lucid.h"
#include <list>

namespace Bullets{

extern int BulletWidth;
extern int BulletHeight;
	
	void Draw();
	void Clear();
	void AddBullet(int type, int x, int y, double direction, double speed, int life = 40);
	void Update();
	
	
	class Bullet : public System::Graphics::Sprite {
	public:
		System::Math::Vector2D Velocity;
		void Init(int type, int x, int y, double direction, double speed, int life);
		bool Update();
		int Life;
	};
	
	
	extern std::list<Bullet*> BulletPool;

}



#endif
