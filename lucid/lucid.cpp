#include "lucid.h"

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "graphics/SDL_gfx/SDL_framerate.h"

namespace System {


	int Width;
	int Height;
	std::string Title;
	SDL_Surface *Screen;
	bool Going;
	FPSmanager fpsm;
	int m_FPS;
	Uint32 timeNow;
	Uint32 timeLast;
	int numFrames;
	int CameraX;
	int CameraY;

	bool Initialize (int w, int h, bool fullScreen, System::State* StartingState, int FrameRate, std::string windowTitle, std::string iconFile){
	
	    // Initiate SDL
	    if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0 ){
			fprintf( stderr, "Video query failed: %s\n", SDL_GetError());
			exit(1);
	        return false;
		}
	    
	    atexit(SDL_Quit); // At quit, destroy SDL
		
		int flags;
		if(fullScreen)
			flags = SDL_HWSURFACE | SDL_HWACCEL | SDL_DOUBLEBUF | SDL_FULLSCREEN;
		else
			flags = SDL_HWSURFACE | SDL_HWACCEL | SDL_DOUBLEBUF;

		Screen = SDL_SetVideoMode(w, h, 32, flags);
		if(Screen == NULL){
			fprintf( stderr, "Video mode set failed: %s\nWidth(%d), Height(%d)\n", SDL_GetError(), w, h);
			exit(1);
			return false;
		}

		/*
	    // Set up the window and video mode
	    if(fullScreen)
	        Screen = SDL_SetVideoMode(w,h,32,SDL_OPENGL|SDL_HWSURFACE|SDL_NOFRAME|SDL_DOUBLEBUF|SDL_FULLSCREEN|SDL_OPENGL);
	    else
	        Screen = SDL_SetVideoMode(w,h,32,SDL_OPENGL|SDL_HWSURFACE|SDL_NOFRAME|SDL_DOUBLEBUF|SDL_OPENGL);
	    if ( Screen == NULL )
	        return false;
		*/





		
	    
		// Set the caption of the window
		SDL_WM_SetCaption(windowTitle.c_str(), NULL);
		
		// Set the window icon
		if(iconFile != ""){
			SDL_Surface* WindowIcon = IMG_Load(iconFile.c_str());
			if(WindowIcon){
				SDL_SetColorKey(WindowIcon, SDL_SRCCOLORKEY, 
					SDL_MapRGB(WindowIcon->format, 255, 0, 255));
				SDL_WM_SetIcon(WindowIcon, NULL);
				SDL_FreeSurface(WindowIcon);
			} else {
				fprintf( stderr, "Error loading window icon file \"%s\"\n", iconFile.c_str());
			}
		}

		// Input
		System::Input::Initialize();

		// Math
		System::Math::Initialize();

		// Text
		if(System::Text::Initialize() == false){
			fprintf( stderr, "Error initializing text\n");
		}
		

		// Framerate
		SDL_initFramerate(&fpsm);
		if(FrameRate < 0) FrameRate = 1;
		SDL_setFramerate(&fpsm, FrameRate);
	    
	    // Default values
	    Width = w;
	    Height = h;
		Title = windowTitle;
		SetState(StartingState);
		Going = true;
	    
	    return true;
	}

	int DesiredFPS(){
		return SDL_getFramerate(&fpsm);
	}
	
	int FPS(){
		return m_FPS;
	}

	void SetWindowTitle(std::string title){
	    SDL_WM_SetCaption(title.c_str(), NULL);
	}
	int CameraCenterX(){
		return CameraX + System::Width/2;
	}
	
	int CameraCenterY(){
		return CameraY + System::Height/2;
	}
 
	void MainLoop(){
		while(Going){
    		SDL_Event event;
			System::Input::Update();
    		while ( SDL_PollEvent(&event) ){
				switch(event.type){
		        case SDL_QUIT:
					return; // Break from main loop
					break;
		        case SDL_KEYDOWN:
					if(CurrentGameState)
						CurrentGameState->KeyDown(event.key.keysym.sym);
					else
						if(event.key.keysym.sym == SDLK_ESCAPE)
							return;
					if(event.key.keysym.sym == SDLK_F12)
						TakeScreenshot();
					break;
		        case SDL_KEYUP:
					if(CurrentGameState)
						CurrentGameState->KeyUp(event.key.keysym.sym);
					break;
				case SDL_MOUSEMOTION:
					if(CurrentGameState)
						CurrentGameState->MouseMotion();
					break;
				case SDL_MOUSEBUTTONDOWN:
					if(CurrentGameState)
						CurrentGameState->MouseButtonDown(event.button.button);
					break;
				case SDL_MOUSEBUTTONUP:
					if(CurrentGameState)
						CurrentGameState->MouseButtonUp(event.button.button);
					break;
		        default:
					break;
		    	}
				if(CurrentGameState)
					CurrentGameState->CheckGUIObjectsEvent(&event);
			}

			if(CurrentGameState){
				CurrentGameState->Update(); // Game Logic
				CurrentGameState->UpdateGUIObjects();
			}
			// Paint screen
			SDL_Flip(Screen);
	  		SDL_FillRect(Screen, NULL, 0); // Clear the buffer black
			
			if(CurrentGameState){
				CurrentGameState->Draw(); // Draw
				CurrentGameState->DrawGUIObjects();
			}else
				System::Graphics::DrawFilledTriangle(System::Width/2, 1, System::Width - 1, System::Height - 1, 1, System::Height - 1, 0, 0, 255, 255);

			// Provide time delay
			SDL_framerateDelay(&fpsm);

			// Calculate FPS
			timeNow = SDL_GetTicks();
			if(timeNow - timeLast > 1000){
				m_FPS = numFrames;
				timeLast = timeNow;
				numFrames = 0;
			} else {
				numFrames++;
			}
		}

		// Close data
		System::Graphics::Image::Close();
		System::Text::Close();
		SDL_Quit();
	}

	void CenterCamera(int x, int y){
		System::CameraX = x - System::Width/2;
		System::CameraY = y - System::Height/2;
	}

	void TakeScreenshot(){
		// Find where to save the file
		int x = 1;
		while(System::File::Exists("screenshot" + System::Text::ToString(x) + ".bmp")){
			x++;
		}
		std::string filename = "screenshot" + System::Text::ToString(x) + ".bmp";
		SDL_SaveBMP(System::Screen, filename.c_str());
	}

	
}


