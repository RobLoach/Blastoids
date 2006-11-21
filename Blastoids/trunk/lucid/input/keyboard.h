#if !defined(_KEYBOARD_H_INCLUDED_)
#define _KEYBOARD_H_INCLUDED_

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h> 


namespace System{
namespace Input{

	bool InitializeKeyboard();
	bool KeyDown(int key);
	void KeyRepeat(int delay = 400, int interval = 30);
	void UpdateKeyboard();

}
}


#endif // _KEYBOARD_H_INCLUDED_


