#if !defined(_BASE_H_INCLUDED_)
#define _BASE_H_INCLUDED_

// Input
#include "input/input.h"

// File
#include "file/file.h"

// Graphics
#include "graphics/graphics.h" 

// Time
#include "time/time.h"

// Math
#include "math/math.h"

// Audio
#include "audio/audio.h"

// Text
#include "text/text.h"
#include "text/encoding.h"

// GUI
#include "gui/gui.h"

// States
#include "statemachine/statemachine.h"

// Particles
#include "particles/particles.h"

// Scripting
#include "scripting/script.h"

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h> 
//#include <gl/gl.h>

namespace System {

	bool Initialize (int w = 400, int h = 300, bool fullScreen = false, System::State* StartingState = NULL, int FrameRate = 60, std::string windowTitle = "Lucid Engine", std::string iconFile = "");
	void MainLoop();

	bool keyDown(int key);
	void SetWindowTitle(std::string title);
	int FPS();
	int DesiredFPS();
	void CenterCamera(int x, int y);

	void TakeScreenshot();

	extern int Width;
	extern int Height;
	extern std::string Title;
	extern SDL_Surface *Screen;
	extern bool Going;
	extern int CameraX;
	extern int CameraY;
	int CameraCenterX();
	int CameraCenterY();

	// Time related
	extern int TickCount;
	extern Uint32 NextTime;

} // end namespace

#endif // _BASE_H_INCLUDED_


