#if !defined(_MOUSE_H_INCLUDED_)
#define _MOUSE_H_INCLUDED_

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "../graphics/sprite.h"


namespace System{
namespace Input{

	int MouseX();
	int MouseY();
	bool MouseButtonDown(int button);
	bool MouseInBounds(int x1, int y1, int x2, int y2);
	bool MouseInBounds(System::Graphics::Sprite* sprite);
	bool ShowMouse(bool show);
	bool ShowMouse();
	bool InitializeMouse();

	void UpdateMouse();

}
}


#endif // _MOUSE_H_INCLUDED_


