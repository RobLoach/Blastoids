#if !defined(_STATEMACHINE_H_INCLUDED_)
#define _STATEMACHINE_H_INCLUDED_

#include "../gui/gui.h"
#include <string>
#include <vector>

namespace System{

	class State;

	extern State* LastGameState;
	extern State* CurrentGameState;
	void SetLastState();
	void SetState(State* state);
	
	class State{
	public:
	
		virtual void Enter(){ }
		virtual void Update(){ }
		virtual void Draw(){ }
		virtual void DrawAfterGUI(){ }
		virtual void KeyDown(int key){ }
		virtual void KeyUp(int key){ }
		virtual void MouseButtonDown(int button){ }
		virtual void MouseButtonUp(int button){ }
		virtual void MouseMotion(){ }
		virtual void Exit(){ }
		virtual void Initialize(){ }

		void AddGUIObject(System::GUI::BaseGUIObject* object);
		void UpdateGUIObjects();
		void DrawGUIObjects();
		void CheckGUIObjectsEvent(const SDL_Event *event);
		void SetGUIObjectFocus(System::GUI::BaseGUIObject* object);

		State(){ GUIObjectFocus = NULL; m_initialized = false; }
		virtual ~State(){ GUIObjects.clear(); }
		State(std::string name){ Name(name); }
	
		std::string Name(){ return m_name; }
		std::string Name(std::string name){ m_name = name; return m_name; }

		bool Initialized(){ return m_initialized; }
		bool Initialized(bool init){ return m_initialized = init; }
	protected:
		std::string m_name;
		bool m_initialized;
	private:
		System::GUI::BaseGUIObject* GUIObjectFocus;
		std::vector<System::GUI::BaseGUIObject*> GUIObjects;
	};
}



#endif
