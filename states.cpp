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



#include <string>

#include "states.h"
#include "lucid/lucid.h"
#include "player.h"
#include "asteroids.h"
#include "bullets.h"
#include "powerups.h"


CHighScoreState* HighScoreState;
CHighScoreBackButton* HighScoreBackButton;
CHighScoreTextBox* HighScoreTextBox;
CMainMenu* MainMenu;
CMainMenuState* MainMenuState;
COptionsMenu* OptionsMenu;
COptionsState* OptionsState;
CGameState* GameState;
CGamePauseState* GamePauseState;
CGamePauseMenu* GamePauseMenu;
CGameScore* GameScore;
CGameOver* GameOver;
std::string MusicMenu;
std::string MusicGame;
bool HighDetail;
bool ShowFPS;
bool MusicOn;
System::Graphics::Sprite Background;
System::Graphics::ParticleSystem Particles;

void DisplayFPS(){
	if(ShowFPS)
		System::Text::Print(System::Width,System::Height,"FPS: " + System::Text::ToString(System::FPS()),150,10,10,255,2,2,"Small");
}

void StartGame(){
	System::SetState(GameState);
	Player.Initialize();
	Player.PrepareForGame();
	Score = 0;
	Asteroids::Clear();
	Bullets::Clear();
	Player.Status(1);
	Level = 0;
	Player.Shields(100);
	Player.Hull(100);
	Player.Lives(3);
	LevelUp();
	System::Audio.Play("MusicGame");
}

void LevelUp(){
	Level++;
	Player.PrepareForGame();
	for(int x = 0; x<Level/3; x++){
		Asteroids::AddAsteroid(0);
	}
	for(int x = 0; x<Level/2; x++){
		Asteroids::AddAsteroid(1);
	}
	for(int x = 0; x<Level; x++){
		Asteroids::AddAsteroid(2);
	}
//Asteroids::AddAsteroid(2);
}
void EndGame(){
	System::SetState(MainMenuState);
	Asteroids::Clear();
	Bullets::Clear();
	PowerUps::Clear();
	Player.Status(0);
	for(int x = 0; x<3; x++)
		Asteroids::AddAsteroid();
	System::Audio.Play("MusicMenu");
}

void COptionsMenu::Initialize(){
	ItemSpacing(20);

	// Change look
	Items.BackColour(50,200,90,170);
	Items.HoverColour(220,10,10,250);
	Items.BorderColour(0,0,0,255);
	Items.TextColour(255,255,0);

	// Location
	Width(200);
	Height(40);
	x(System::Width/2 - Width()/2);
	y(100);

	if(Player.MouseControl())
		AddItem("Controller: Mouse");
	else
		AddItem("Controller: Keyboard");
	if(HighDetail)
		AddItem("Detail: High");
	else
		AddItem("Detail: Low");
	if(MusicOn){
		AddItem("Music: On");
		System::Audio.MusicVolume(50);
	}else{
		AddItem("Music: Off");
		System::Audio.MusicVolume(0);
	}
	AddItem("Back");

}

void COptionsMenu::Select(std::string item){
	if(item == "Controller: Keyboard"){
		ItemText("Controller: Keyboard", "Controller: Mouse");
		Player.MouseControl(true);
	} else if(item == "Controller: Mouse"){
		ItemText("Controller: Mouse", "Controller: Keyboard");
		Player.MouseControl(false);
	} else if(item == "Detail: Low"){
		ItemText("Detail: Low", "Detail: High");
		HighDetail = true;
	} else if(item == "Detail: High"){
		ItemText("Detail: High", "Detail: Low");
		HighDetail = false;
	} else if(item == "Music: On"){
		ItemText("Music: On", "Music: Off");
		MusicOn = false;
		System::Audio.MusicVolume(0);
	} else if(item == "Music: Off"){
		ItemText("Music: Off", "Music: On");
		MusicOn = true;
		System::Audio.MusicVolume(50);
	} else if(item == "Back"){
		System::SetState(MainMenuState);
	}
}

void COptionsState::Initialize(){
	AddGUIObject(GameScore);
	AddGUIObject(OptionsMenu);
}

void COptionsState::Draw(){
	Background.Draw();
	Asteroids::Draw();
	Particles.Draw();
	DisplayFPS();
}
void COptionsState::Update(){
	Asteroids::Update();
	Particles.Update();
}

void COptionsState::Exit(){
	System::Audio.Play("SoundAsteroidHit");
}




void CHighScoreState::KeyDown(int key){
	System::SetState(MainMenuState);
}

void CHighScoreState::Update(){
	Asteroids::Update();
	Particles.Update();
}

void CHighScoreState::Exit(){
	System::Audio.Play("SoundAsteroidHit");
}

void CHighScoreState::Draw(){
	Background.Draw();
	Asteroids::Draw();
	Particles.Draw();
	for(int i = 0; i < 10; i++){
		System::Text::Print(System::Width/2, 20 + i * 30,
				System::Text::ToString(i+1) + ". " + Highscores.Name(i) + " - " + System::Text::ToString(Highscores.Score(i)),
				180,180,180,255,1,1,"Medium");
	}
	DisplayFPS();
}

void CHighScoreState::Initialize(){
	AddGUIObject(GameScore);
	AddGUIObject(HighScoreBackButton);
	Highscores.Load("scores.dat");
}

void CGameScore::Initialize(){
	x(0);
	y(0);
	Width(System::Width);
	Height(System::Height);
	HorizontalAlignment(0);
	VerticalAlignment(0);
	TextColour(0,255,0);
}

void CGameScore::Update(){
	Text(std::string("Score: ") + System::Text::ToString(Score));
}


void CMainMenuState::Enter(){
}

void CMainMenuState::Exit(){
	System::Audio.Play("SoundAsteroidHit");
}

void CMainMenuState::Initialize(){
	
	// Load data	
	System::Text::LoadFont("Big", System::Script["FontFile"].ToString(), 32);
	System::Text::LoadFont("Small", System::Script["FontFile"].ToString(), 14);
	System::Text::LoadFont("Medium", System::Script["FontFile"].ToString(), 17);

	System::Graphics::Image::Load("AsteroidsLarge",System::Script["AsteroidsLarge"].ToString());
	System::Graphics::Image::Load("AsteroidsMedium",System::Script["AsteroidsMedium"].ToString());
	System::Graphics::Image::Load("AsteroidsSmall",System::Script["AsteroidsSmall"].ToString());
	System::Graphics::Image::Load("Ship",System::Script["Ship"].ToString());
	System::Graphics::Image::Load("Bullets",System::Script["Bullets"].ToString());
	System::Graphics::Image::Load("Background",System::Script["Background"].ToString());
	System::Graphics::Image::Load("PowerUps",System::Script["PowerUps"].ToString());

	//System::Graphics::Image::Load("Angels","angels.png", 0,0,72,128);
	//Angels.Load("Angels",24,32);
	//Angels.Tile(1,2);
	//Angels.Alpha(50);
	//Angels.Position(System::Width/2, System::Height/2);
	//Angels.TransColour(255,0,255);


	System::Graphics::Image::TransColour("AsteroidsLarge",255,0,255);
	System::Graphics::Image::TransColour("AsteroidsMedium",255,0,255);
	System::Graphics::Image::TransColour("AsteroidsSmall",255,0,255);
	System::Graphics::Image::TransColour("Ship",255,0,255);
	System::Graphics::Image::TransColour("Bullets",255,0,255);
	System::Graphics::Image::TransColour("PowerUps",255,0,255);

	Asteroids::AsteroidLargeWidth = 150;//System::Script["AsteroidLargeWidth"];
	Asteroids::AsteroidLargeHeight = 150;//System::Script["AsteroidLargeHeight"];
	Asteroids::AsteroidMediumWidth = 80;//System::Script["AsteroidMediumWidth"];
	Asteroids::AsteroidMediumHeight = 80;//System::Script["AsteroidMediumHeight"];
	Asteroids::AsteroidSmallWidth = 30;//System::Script["AsteroidSmallWidth"];
	Asteroids::AsteroidSmallHeight = 30;//System::Script["AsteroidSmallHeight"];
	Bullets::BulletWidth = 13;//System::Script["BulletsWidth"];
	Bullets::BulletHeight = 13;//System::Script["BulletsHeight"];
	PowerUps::PowerUpsWidth = 16;//System::Script["BulletsWidth"];
	PowerUps::PowerUpsHeight = 16;//System::Script["BulletsHeight"];

	System::Audio.Load("MusicMenu", System::Script["MusicMenu"].ToString());
	System::Audio.Load("MusicGame", System::Script["MusicGame"].ToString());
	System::Audio.Load("MusicGameOver", System::Script["MusicGameOver"].ToString());



	System::Audio.Load("SoundAsteroidHit", System::Script["SoundAsteroidHit"].ToString());
	System::Audio.Load("SoundAsteroidExplode", System::Script["SoundAsteroidExplode"].ToString());
	System::Audio.Load("SoundShoot", System::Script["SoundShoot"].ToString());
	System::Audio.Load("SoundEngine", System::Script["SoundEngine"].ToString());
	System::Audio.Load("SoundPlayerExplode", System::Script["SoundPlayerExplode"].ToString());
	System::Audio.Load("SoundPlayerHit", System::Script["SoundPlayerHit"].ToString());
	System::Audio.Load("SoundPowerup", System::Script["SoundPowerup"].ToString());
	System::Audio.Load("SoundPlayerStart", System::Script["SoundPlayerStart"].ToString());

	MusicOn = true;
	System::Audio.MusicVolume(MusicOn ? 50 : 0);
	ShowFPS = true;
	HighDetail = true;

	Background.Load("Background");

	Player.Initialize();
	Player.MouseControl(true);

	// Add the GUI objects
	AddGUIObject(GameScore);
	AddGUIObject(MainMenu);

}

void CMainMenuState::Update(){
	//Player.Update();
	//Background.Rotate(2);
	Asteroids::Update();
	PowerUps::Update();
	Particles.Update();
}

void CMainMenuState::Draw(){
	Background.Draw();
	Player.Paint();
	Asteroids::Draw();
	PowerUps::Draw();
	Particles.Draw();
	System::Text::Print(System::Width/2,100,
		"Blastoids",200,20,20,200,1,1,"Big");
	DisplayFPS();
}
void CMainMenuState::DrawAfterGUI(){
	//Player.Paint();
}









	void CMainMenu::Initialize(){
		// Add some items to it
		AddItem("Start Game");
		AddItem("Options");
		AddItem("Highscores");
		AddItem("Exit");
		ItemSpacing(13);

		// Change look
		Items.BackColour(180,10,10,170);
		Items.HoverColour(220,10,10,250);
		Items.BorderColour(0,0,0,255);
		Items.TextColour(0,0,0);

		// Location
		Width(200);
		Height(40);
		x(System::Width/2 - Width()/2);
		y(120);

		EndGame();
	}

	void CMainMenu::Select(std::string item){
		if(item == "Start Game"){
			StartGame();
		} else if(item == "Options"){
			System::SetState(OptionsState);
		} else if(item == "Highscores"){
			System::SetState(HighScoreState);
			//rand = System::Math::RandomNumber((int)(-0.5*100), (int)((0.5*100)/10));
			//rand = System::Math::RandomNumber(50100);
		} else if(item == "Exit"){
			System::Going = false;
		}
	}




	void CGameState::Initialize(){
		AddGUIObject(GameScore);
	}
	void CGameState::Update(){
		Particles.Update();
		Player.Update();
		Asteroids::Update();
		Bullets::Update();
		PowerUps::Update();
	}

	void CGameState::MouseButtonDown(int button){

		//for(int x = 0; x < 100; x++)
		//	System::Particles::AddParticlePixel(System::Input::MouseX(), System::Input::MouseY(), RAD2DEG(System::Math::RandomNumber(0,360)), 2, 20, 255, 100, 0, 255);
		//Particles.AddPixelExplosion(150, System::Input::MouseX(), System::Input::MouseY(), 2, 1, 50, 25, 0, 0, 0);
		//x, y, speed, speedChange, life, lifeChange, Uint8 colourR, Uint8 colourG, Uint8 colourB
	}
	void CGameState::KeyDown(int key){
		switch(key){
		case SDLK_ESCAPE:
			System::SetState(GamePauseState);
			break;
		}
		//for(int x = 0; x < 100; x++)
		//	Particles.AddParticleSprite(System::Width, System::Height, RAD2DEG(System::Math::RandomNumber(0,360)), 3, 50, "Bullets", 0, 0, 13, 13);

		

	}
	void CGameState::Draw(){
		Background.Draw();
		Asteroids::Draw();
		Player.Paint();
		Particles.Draw();
		Bullets::Draw();
		PowerUps::Draw();
		DisplayFPS();
	}



	void CGamePauseState::Initialize(){
		AddGUIObject(GameScore);
		AddGUIObject(GamePauseMenu);
	}



void CGamePauseState::Exit(){
	System::Audio.Play("SoundAsteroidHit");
}

	void CGamePauseState::Update(){
		//Particles.Update();
		//Player.Update();
		//Asteroids::Update();
		//Bullets::Update();
	}
	void CGamePauseState::Draw(){
		Background.Draw();
		Player.Paint();
		Asteroids::Draw();
		Particles.Draw();
		Bullets::Draw();
	PowerUps::Draw();
	DisplayFPS();
	}

	void CGamePauseState::KeyDown(int key){
		switch(key){
		case SDLK_ESCAPE:
			System::SetState(GameState);
		}
	}


	void CGamePauseMenu::Initialize(){
		ItemSpacing(20);
	
		// Change look
		Items.BackColour(50,200,90,170);
		Items.HoverColour(220,10,10,250);
		Items.BorderColour(0,0,0,255);
		Items.TextColour(255,255,0);
	
		// Location
		Width(200);
		Height(40);
		x(System::Width/2 - Width()/2);
		y(100);
	
		AddItem("Resume");
		AddItem("Leave Game");
	}

	void CGamePauseMenu::Select(std::string item){
		if(item == "Resume"){
			System::SetState(GameState);
		} else if(item == "Leave Game"){
			Player.Status(0);
			System::SetState(GameOver);
		}
	}

	void CHighScoreBackButton::Initialize(){
		Width(120);
		Height(50);
		x(System::Width/2 - Width()/2);
		y(System::Height - Height() - 20);
		Text("Okay");
		BackColour(50,200,100,100);
		TextColour(255,200,100);
		HoverColour(100,200,50,150);
	}

	void CGameOver::Initialize(){
		AddGUIObject(HighScoreBackButton);
		AddGUIObject(GameScore);
		AddGUIObject(HighScoreTextBox);
	}

	void CGameOver::Enter(){
		System::Audio.Play("MusicGameOver");
	}

	void CGameOver::Exit(){
		System::Audio.Play("MusicMenu");
		System::Audio.Play("SoundAsteroidHit");
		HighScoreState->Highscores.AddRecord(HighScoreTextBox->Text(), Score);
	}

	void CGameOver::Draw(){
		Background.Draw();
		Player.Paint();
		Asteroids::Draw();
		Particles.Draw();
		Bullets::Draw();
	PowerUps::Draw();
		System::Text::Print(System::Width/2,System::Height/2,"Game Over",255,20,20,220,1,2,"Big");
		DisplayFPS();
	}
	void CGameOver::Update(){
		Particles.Update();
		Player.Update();
		Asteroids::Update();
		Bullets::Update();
	PowerUps::Update();
	}

	void CHighScoreBackButton::Click(){
		System::SetState(MainMenuState);
	}



void CHighScoreTextBox::Initialize(){
	this->Width(200);
	this->Height(30);
	this->x(System::Width/2-this->Width()/2);
	this->y(System::Height/2+this->Height()/2);
	this->Text("Type Your Name");
	this->MaxCharacters(10);
}

void CHighScoreTextBox::Enter(){
	//HighScoreBackButton->Click();
}
