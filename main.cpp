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

#include "lucid/lucid.h"

#include "states.h"
#include "player.h"
#include "bullets.h"
#include "powerups.h"
#include "asteroids.h"
#include "states.h"


// The main game state


// The main menu

// The main game state


int main(int argc, char *argv[]){
	MainMenuState = new CMainMenuState;
	MainMenu = new CMainMenu;
	HighScoreState = new CHighScoreState;
	HighScoreBackButton = new CHighScoreBackButton;
	HighScoreTextBox = new CHighScoreTextBox;
	OptionsMenu = new COptionsMenu;
	OptionsState = new COptionsState;
	GameState = new CGameState;
	GamePauseState = new CGamePauseState;
	GamePauseMenu = new CGamePauseMenu;
	GameScore = new CGameScore;
	GameOver = new CGameOver;

	if(!System::Script.LoadFile("config.dat")){
		fprintf(stderr, "%s", System::Script.GetLastError().c_str());
	}
	HighDetail = System::Script["HighDetail"];
	ShowFPS = System::Script["ShowFPS"];
	MusicOn = System::Script["MusicOn"];

	System::Initialize(600, 400, false,
			MainMenuState, 50, "Blastoids",
			System::Script["Icon"].ToString()
		);

	System::MainLoop();
	
	Asteroids::Clear();
	Bullets::Clear();
	delete OptionsState;
	delete OptionsMenu;
	delete MainMenuState;
	delete MainMenu;
	delete HighScoreState;
	delete HighScoreBackButton;
	delete HighScoreTextBox;
	delete GameState;
	delete GamePauseState;
	delete GamePauseMenu;
	delete GameScore;
	delete GameOver;
	
	return 0;
}






