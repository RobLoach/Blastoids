#if !defined(_LABEL_H_)
#define _LABEL_H_

#include <string>
#include "baseguiobject.h"
#include <SDL/SDL.h>
#include "../text/text.h"
#include "../input/input.h"
#include "../graphics/primitives.h"

namespace System{
namespace GUI{


class Label : public System::GUI::GUIObject
{
	protected:
		std::string m_text;
		std::string m_font;
		Uint8 m_textcolourR;
		Uint8 m_textcolourG;
		Uint8 m_textcolourB;
		int m_hAlignment;
		int m_vAlignment;
	public:
	Label() : m_text("Label"),
				m_font("default"),
				m_textcolourR(255),
				m_textcolourG(255),
				m_textcolourB(255),
				m_hAlignment(1),
				m_vAlignment(1)
	{
		Type(2);
		Height(0);
		Width(0);
	}

	void Draw();

	std::string Text(std::string text){ return m_text = text; }
	std::string Text(){ return m_text; }

	std::string Font(std::string font){ return m_font = font; }
	std::string Font(){ return m_font; }

	int HorizontalAlignment(int halign);
	int HorizontalAlignment();

	int VerticalAlignment(int valign);
	int VerticalAlignment();

	void TextColour(int r, int g, int b){
		m_textcolourR = r; m_textcolourG = g; m_textcolourB = b;
	}

};

}
}

#endif

