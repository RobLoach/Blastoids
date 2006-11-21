#include "statemachine.h"

#include <vector>
#include <algorithm>

namespace System{
 
	State* LastGameState;
	State* CurrentGameState;

	void SetLastState(){
		State* temp = CurrentGameState;
		CurrentGameState = LastGameState;
		LastGameState = temp;
	}

	void SetState(State* state){
		// Make the current one the last one
		State* newlast = CurrentGameState;
		if(CurrentGameState != NULL){
			CurrentGameState->Exit();
			CurrentGameState->SetGUIObjectFocus(NULL);
		}

		// Update to the current one
		CurrentGameState = state;
		if(CurrentGameState != NULL){
			if(CurrentGameState->Initialized() == false){
				CurrentGameState->Initialize();
				CurrentGameState->Initialized(true);
			}
			CurrentGameState->Enter();
		}
		LastGameState = newlast;
	}

	void State::AddGUIObject(System::GUI::BaseGUIObject* object){
		GUIObjects.push_back(object);
		if(object->Initialized() == false){
			object->Initialized(true);
			object->Initialize();
		}
		GUIObjectFocus = object;
	}
 
	void State::UpdateGUIObjects(){
		for(std::vector<System::GUI::BaseGUIObject*>::iterator pos = GUIObjects.begin(); pos != GUIObjects.end(); pos++){
			(*pos)->Update();
		}
	}

	void State::CheckGUIObjectsEvent(const SDL_Event *event){
		int mx, my;
		switch(event->type){
        case SDL_KEYUP:
			if(GUIObjectFocus){
				GUIObjectFocus->KeyUp((SDL_KeyboardEvent*)&event->key);
				GUIObjectFocus->KeyUp(event->key.keysym.sym);
			}
			break;
        case SDL_KEYDOWN:
			if(event->key.keysym.sym == SDLK_TAB){
				
				std::vector<System::GUI::BaseGUIObject*>::iterator CurGUIObject = find(GUIObjects.begin(), GUIObjects.end(), GUIObjectFocus);
				if(++CurGUIObject != GUIObjects.end()){
					GUIObjectFocus = *(CurGUIObject);
				} else {
					GUIObjectFocus = *(GUIObjects.begin());
				}
			} else if(GUIObjectFocus){
				GUIObjectFocus->KeyDown((SDL_KeyboardEvent*)&event->key);
				GUIObjectFocus->KeyDown(event->key.keysym.sym);
			}
			break;
		case SDL_MOUSEMOTION:
			mx = System::Input::MouseX();
			my = System::Input::MouseY();
			for(std::vector<System::GUI::BaseGUIObject*>::iterator pos = GUIObjects.begin(); pos != GUIObjects.end(); pos++){
				if((*pos)->MouseIsOver())
					(*pos)->MouseMotion();
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			mx = System::Input::MouseX();
			my = System::Input::MouseY();
			if(GUIObjectFocus){
				GUIObjectFocus->Focus(false);
				GUIObjectFocus = NULL;
			}
			for(std::vector<System::GUI::BaseGUIObject*>::iterator pos = GUIObjects.begin(); pos != GUIObjects.end(); pos++){
				if((mx >= (*pos)->x()) && (mx <= (*pos)->x()+(*pos)->Width()) && (my >= (*pos)->y()) && (my <= (*pos)->y()+(*pos)->Height())){
					(*pos)->MouseButtonDown(event->button.button);
					GUIObjectFocus = (*pos);
					GUIObjectFocus->Focus(true);
				}
			}
			break;
		case SDL_MOUSEBUTTONUP:
			mx = System::Input::MouseX();
			my = System::Input::MouseY();
			for(std::vector<System::GUI::BaseGUIObject*>::iterator pos = GUIObjects.begin(); pos != GUIObjects.end(); pos++){
				if((*pos)->MouseIsOver())
					(*pos)->MouseButtonUp(event->button.button);
			}
			break;
        default:
			break;
    	}
		
	}

	void State::SetGUIObjectFocus(System::GUI::BaseGUIObject* object){
		if(GUIObjectFocus){
			GUIObjectFocus->Focus(false);
			GUIObjectFocus = NULL;
		}
		if(object){
			object->Focus(true);
			GUIObjectFocus = object;
		}
	}

	void State::DrawGUIObjects(){
		//System::Graphics::DrawLine(0,0,500,500,255);
		
		for(std::vector<System::GUI::BaseGUIObject*>::iterator pos = GUIObjects.begin(); pos != GUIObjects.end(); pos++){
			(*pos)->Draw();
		}
		DrawAfterGUI();
	}

}
