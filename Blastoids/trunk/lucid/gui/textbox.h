#if !defined(_TEXTBOX_H_)
#define _TEXTBOX_H_

#include <string>
#include "baseguiobject.h"
#include <SDL/SDL.h>
#include "../text/text.h"
#include "../input/input.h"
#include "../graphics/primitives.h"

namespace System{
namespace GUI{


class TextBox : public GUIObject
{
	protected:
		std::string m_text;
		std::string m_font;
		Uint8 borderR, borderG, borderB, borderA;
		Uint8 backR, backG, backB, backA;
		Uint8 m_textcolourR;
		Uint8 m_textcolourG;
		Uint8 m_textcolourB;
		bool m_Locked;
		int m_MaxCharacters;
	public:
	TextBox() : m_text("TextBox"),
				m_font("default"),
				m_textcolourR(0), m_textcolourG(0), m_textcolourB(0),
				backR(255), backG(255), backB(255), backA(255),
				borderR(100), borderG(100), borderB(100), borderA(255),
				m_Locked(false),
				m_MaxCharacters(-1)
	{
		Type(2);
		Height(70);
	}

	bool Locked(){ return m_Locked; }
	bool Locked(bool locked){ return m_Locked = locked; }

	virtual void Draw(){
		if(Visible()){
			System::Graphics::DrawRectangle(this->x()+System::CameraX,this->y()+System::CameraY,x()+Width()+System::CameraX,y()+Height()+System::CameraY,borderR, borderG, borderB, borderA);
			System::Graphics::DrawFilledRectangle(x()+1+System::CameraX,y()+1+System::CameraY,x()+Width()-1+System::CameraX,y()+Height()-1+System::CameraY,backR, backG, backB, backA);

			System::Text::Print(x()+10+System::CameraX,y()+Height()/2+System::CameraY,m_text,m_textcolourR,m_textcolourG,m_textcolourB,255,0,1,m_font);
		}
	}
	virtual void Enter(){ }

	std::string Text(std::string text){ return m_text = text; }
	std::string Text(){ return m_text; }

	std::string Font(std::string font){ return m_font = font; }
	std::string Font(){ return m_font; }

	int MaxCharacters(){ return m_MaxCharacters; }
	int MaxCharacters(int maxchars){ return m_MaxCharacters = maxchars; }


	void KeyDown(SDL_KeyboardEvent *key);

	

	void BorderColour(int r, int g, int b, int a=255);
	void BackColour(int r, int g, int b, int a=255);
	void TextColour(int r, int g, int b);
};

}
}

#endif

