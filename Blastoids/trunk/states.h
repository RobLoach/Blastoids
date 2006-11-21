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


#if !defined(_STATES_H_)
#define _STATES_H_

#include "lucid/lucid.h"

class CHighScoreState;
class CMainMenuState;
class CMainMenu;
class COptionsMenu;
class COptionsState;
class CGameState;
class CGamePauseState;
class CGamePauseMenu;
class CHighScoreBackButton;
class CHighScoreTextBox;
class CGameScore;

class CGameOver;

extern bool HighDetail;
extern bool ShowFPS;
extern bool MusicOn;
extern System::Graphics::ParticleSystem Particles;

void StartGame();
void LevelUp();

class COptionsMenu : public System::GUI::Menu {

	void Initialize();

	// When an item was selected
	void Select(std::string item);

};


class COptionsState : public System::State {
	void Initialize();
	void Draw();
	void Update();
	void Exit();
};


class CGameOver : public System::State {
	void Initialize();
	void Draw();
	void Update();
	void Enter();
	void Exit();
};


class CHighScoreState : public System::State {
	public:
	System::File::HighScoreList Highscores;
	void KeyDown(int key);
	void Initialize();
	void Draw();
	void Update();
	void Exit();
	~CHighScoreState(){
		Highscores.Save("scores.dat",10);
	}
};



class CMainMenu : public System::GUI::Menu {

	void Initialize();

	// When an item was selected
	void Select(std::string item);

};




class CMainMenuState : public System::State {
	public:
	void Initialize();
	void Update();
	void Draw();
	void DrawAfterGUI();
	void Enter();
	void Exit();
	int rand;
};




class CGameState : public System::State {
	public:
	void Initialize();
	void Update();
	void Draw();
	void KeyDown(int key);
	void MouseButtonDown(int button);
};

class CGameScore : public System::GUI::Label {
	void Initialize();
	void Update();
};

class CGamePauseState : public System::State {
	public:
	void Initialize();
	void Update();
	void Draw();
	void KeyDown(int key);
	void Exit();
};


class CGamePauseMenu : public System::GUI::Menu {

	void Initialize();

	// When an item was selected
	void Select(std::string item);

};


class CHighScoreBackButton : public System::GUI::Button {
	public:
	void Initialize();

	// When an item was selected
	void Click();

};


class CHighScoreTextBox : public System::GUI::TextBox {
	public:
	void Initialize();
	void Enter();
};


extern CHighScoreState* HighScoreState;
extern CMainMenu* MainMenu;
extern CMainMenuState* MainMenuState;
extern COptionsState* OptionsState;
extern COptionsMenu* OptionsMenu;
extern CGameState* GameState;
extern CGamePauseState* GamePauseState;
extern CGamePauseMenu* GamePauseMenu;
extern CHighScoreBackButton* HighScoreBackButton;
extern CHighScoreTextBox* HighScoreTextBox;
extern CGameScore* GameScore;
extern CGameOver* GameOver;


#endif
