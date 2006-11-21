#if !defined(_BASEGUIOBJECT_H_)
#define _BASEGUIOBJECT_H_


#include <SDL/SDL.h>
#include "../graphics/graphics.h"
#include "../input/mouse.h"



namespace System{
namespace GUI{

	
	class BaseGUIObject{
	protected:
		int m_Type;
		bool m_Focus;
		bool m_Initialized;
		bool m_Enabled;
		bool m_Visible;

	public:
		int Type(){ return m_Type; }
		int Type(int type){ return m_Type = type; }

		bool Focus(){ return m_Focus; }
		bool Focus(bool focus){ return m_Focus = focus; }
		
		virtual void MouseMotion(){ }
		virtual void MouseButtonDown(int button){ }
		virtual void MouseButtonUp(int button){ }
		virtual void KeyUp(int key){ }
		virtual void KeyUp(SDL_KeyboardEvent *key){ }
		virtual void KeyDown(int key){ }
		virtual void KeyDown(SDL_KeyboardEvent *key){ }
		virtual void Draw(){ }
		virtual void Update(){ }
		virtual int x(){ }
		virtual int y(){ }
		virtual int Width(){ }
		virtual int Height(){ }
		virtual void Initialize(){ }
		bool Initialized(){ return m_Initialized; }
		bool Initialized(bool init){ return m_Initialized = init; }
		BaseGUIObject() : m_Type(0),
							m_Focus(false),
							m_Initialized(false),
							m_Enabled(true), m_Visible(true)
		{ }
		virtual ~BaseGUIObject(){ }
		virtual bool MouseIsOver(){ return System::Input::MouseInBounds(x(),y(),x()+Width(),y()+Height()); }

		bool Visible(){ return m_Visible; }
		bool Visible(bool visible){ return m_Visible = visible; }
		bool Enabled(){ return m_Enabled; }
		bool Enabled(bool enabled){ return m_Enabled = enabled; }
	};

	class GUIObject : public BaseGUIObject{
	protected:
		int m_x, m_y, m_Height, m_Width;
		
	public:
		GUIObject() :  m_x(0), m_y(0), m_Height(100), m_Width(100) { }
		int x(){ return m_x; }
		int x(int d){ return m_x = d; }
		int y(){ return m_y; }
		int y(int d){ return m_y = d; }

		int Width(){ return m_Width; }
		virtual int Width(int width){ return m_Width = width; }
		int Height(){ return m_Height; }
		virtual int Height(int height){ return m_Height = height; }
		
		virtual void SetPosition(int X, int Y, int width, int height){
			x(X); y(Y); Width(width); Height(height);
		}

		virtual void Draw(){
			if(System::Input::MouseInBounds(m_x,m_y,m_x+m_Width,m_y+m_Height)){
				System::Graphics::DrawRectangle(m_x,m_y,m_x+m_Width,m_y+m_Height,0,255,0,200);
				System::Graphics::DrawFilledRectangle(m_x+1,m_y+1,m_x+m_Width-1,m_y+m_Height-1,0,150,0,200);
			} else {
				System::Graphics::DrawRectangle(m_x,m_y,m_x+m_Width,m_y+m_Height,255,0,0,200);
				System::Graphics::DrawFilledRectangle(m_x+1,m_y+1,m_x+m_Width-1,m_y+m_Height-1,150,0,0,200);
			}
		}
	};


	class GUIObjectSprite : public BaseGUIObject{
	public:
		System::Graphics::Sprite Graphic;
		int x(){ return Graphic.Left(); }
		int x(int d){ return Graphic.Left(d); }
		int y(){ return Graphic.Top(); }
		int y(int d){ return Graphic.Top(d); }

		int Width(){ return Graphic.Width(); }
		int Width(int width){ return 0; }
		int Height(){ return Graphic.Height(); }
		int Height(int height){ return 0; }

		
		virtual void SetPosition(int X, int Y, int width, int height){
			x(X); y(Y); Width(width); Height(height);
		}

		virtual void Draw(){ Graphic.Draw(); }
	};

}
} 

#endif
