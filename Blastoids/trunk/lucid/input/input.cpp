#include "input.h"


namespace System{
namespace Input{

void Initialize(){
	InitializeMouse();
	InitializeKeyboard();
}

void Update(){
	UpdateKeyboard();
	UpdateMouse();
}

}
}
