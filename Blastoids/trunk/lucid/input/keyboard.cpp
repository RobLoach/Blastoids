#include "keyboard.h"

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>


namespace System{
namespace Input{

	Uint8* keys;

	bool KeyDown(int key) { return (bool)keys[key]; }
	void KeyRepeat(int delay, int interval){
		SDL_EnableKeyRepeat(delay, interval);
	}
	bool InitializeKeyboard(){
		SDL_EnableUNICODE(1); // Enable unicodezorz
	}

	void UpdateKeyboard(){ keys = SDL_GetKeyState(NULL); }


}
}



