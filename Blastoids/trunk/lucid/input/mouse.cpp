#include "mouse.h"

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>


namespace System{
	extern int CameraX;
	extern int CameraY;
namespace Input{
	int mousex, mousey;
	Uint8 buttons;
	
	int MouseX(){
		return mousex + CameraX;
	}
	int MouseY(){
		return mousey + CameraY;
	}

	bool MouseButtonDown(int button){
		return buttons & SDL_BUTTON(button);
	}

	bool MouseInBounds(int x1, int y1, int x2, int y2){
		int x = MouseX();
		int y = MouseY();
		return (x >= x1) && (x <= x2) && (y >= y1) && (y <= y2);
	}

	
	bool ShowMouse(bool show){
		if(show)
			SDL_ShowCursor(SDL_ENABLE);
		else
			SDL_ShowCursor(SDL_DISABLE);
		return show;
	}

	bool MouseInBounds(System::Graphics::Sprite* sprite){
		return MouseInBounds(sprite->Left(), sprite->Top(), sprite->Right(), sprite->Bottom());
	}

	bool ShowMouse(){
		return (SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE);
	}

	bool InitializeMouse(){
		// Initialize mouse
	}

	void UpdateMouse(){
		buttons = SDL_GetMouseState(&mousex, &mousey);
	}

}
}



