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


#if !defined(_POWERUPS_H_)
#define _POWERUPS_H_

#include "lucid/lucid.h"
#include "player.h"

namespace PowerUps {

extern int PowerUpsWidth;
extern int PowerUpsHeight;



class CPowerUp : public System::Graphics::Sprite {
public:

	bool Update();

	void Init(int type, int x, int y);

private:
	int m_life;
	int m_type;
};

void Draw();
void Update();
void Clear();
void AddPowerUp(int x, int y);

}

#endif
