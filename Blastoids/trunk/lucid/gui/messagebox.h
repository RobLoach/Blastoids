#if !defined(_MESSAGEBOX_H_)
#define _MESSAGEBOX_H_

#include <string>
#include "baseguiobject.h"
#include "button.h"
#include <SDL/SDL.h>
#include "../text/text.h"
#include "../input/mouse.h"
#include "../graphics/primitives.h"

namespace System{
namespace GUI{



class MessageBox : public virtual System::GUI::GUIObject {
	protected:
		std::string m_text;
		std::string m_title;
		std::string m_font;
		std::string m_fontTitle;
		Uint8 borderR, borderG, borderB, borderA;
		Uint8 backR, backG, backB, backA;
		Uint8 backTitleR, backTitleG, backTitleB, backTitleA;
		Uint8 textR, textG, textB;
		Uint8 textTitleR, textTitleG, textTitleB;
		int m_titleheight;

		Button* m_button;
	public:

	MessageBox() : 	m_text("Message"), m_title("MessageBox"),
				m_font("default"), m_fontTitle("default"),
				backR(150), backG(150), backB(150), backA(255),
				borderR(200), borderG(200), borderB(200), borderA(255),
				backTitleR(200), backTitleG(200), backTitleB(200), backTitleA(255),
				textR(200), textG(200), textB(200),
				textTitleR(200), textTitleG(200), textTitleB(200)
	{
		Type(4);
		Height(250);
		Width(200);
	}

	
	void BorderColour(int r, int g, int b, int a){
		borderR = r;  borderG = g; borderB = b; borderA = a;
	}
	void BackColour(int r, int g, int b, int a){
		backR = r; backG = g; backB = b; backA = a;
	}
	void BackTitleColour(int r, int g, int b, int a){
		backTitleR = r; backTitleG = g; backTitleB = b; backTitleA = a;
	}
	void TextColour(int r, int g, int b){
		textR = r; textG = g; textB = b;
	}
	void TextTitleColour(int r, int g, int b){
		textTitleR = r; textTitleG = g; textTitleB = b;
	}
	int TitleHeight(int height){ return m_titleheight = height; }
	int TitleHeight(){ return m_titleheight; }

	void Draw();

	std::string Text(std::string text){ return m_text = text; }
	std::string Text(){ return m_text; }

	std::string Title(std::string title){ return m_title = title; }
	std::string Title(){ return m_title; }

	std::string Font(std::string font){ return m_font = font; }
	std::string Font(){ return m_font; }

	std::string TitleFont(std::string fontTitle){ return m_fontTitle = fontTitle; }
	std::string TitleFont(){ return m_fontTitle; }

	//void Button(Button* button){ m_button = button; }

	virtual void Click(){ }

	virtual void MouseButtonDown(int button){
		
	}
	// TODO

};


}
}

#endif

